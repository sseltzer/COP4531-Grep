

#include "vector.h"#include <string>
#include <fstream>
#include "nfa.h"

#define NUM_OF_FLAGS 10;

typedef std::string            String;
typedef fsu::Vector<String>    Vector;

class Grep
{
public:
           Grep       ();
    bool   setFlag    (const char* flag);
    bool   processing (const Vector files);
    Vector results    ();
    bool   search     (char* search);
private:
    bool   flagSet_[10];
    Vector results_;
    Vector flag_;
    const char * search_ = NULL;
    
};

Grep::Grep()
{
    for( size_t ctr = 0; ctr < 10; ++ctr )
        flagSet_[ctr] = false;
}

bool Grep::setFlag(const char* flagSet)
{
    flagSet_[0] = true;//-i
    flagSet_[1] = true;//-l
    flagSet_[2] = true;//-n
    //std::cout << "Set " << flagSet << " flag\n";
        return true;
}

bool Grep::processing (Vector files)
{
    
    std::ifstream inStream;
    String line,temp;
    size_t lineNumber = 0;
   
    
    for (size_t counter = 0; counter < files.Size(); ++counter)
    {
        //open file
        inStream.open(files[counter]);
        if (inStream.fail())
        {
            std::cout << "grep: " << files[counter] << ": No such file or directory\n";
            return false;
        }
        
        if (search_ == NULL)
        {
            std::cout << "Search parameter not set\n";
            return false;
        }
        
        Nfa nfa(search_);
        if (flagSet_[2] == true)
        {   //add line with file name
            results_.PushBack(files[counter]);
        }
        while (!inStream.eof())
        {
            std::getline(inStream,line,'\n');
            ++lineNumber;
            
            if( nfa.Matches( line.c_str() ) )
            {
                if(flagSet_[1] == true)
                {   //add line number
                    temp = "Line [" + std::to_string(lineNumber) + "] : " + line;
                    line = temp ;
                }
                if (flagSet_[2] == true)
                {
                    line = "    " + line;
                }
                //if flag set add line number to front of line
                results_.PushBack(line);
            }
            line.clear();
        }
        lineNumber = 0;
    }
    return true;
}

Vector Grep::results()
{
    return results_;
}

bool Grep::search(char* search)
{
    
    size_t ind = 0;
    if (sizeof(*search) == 0) { std::cout << "Search is zero length\n "; return false;}
    if (search == NULL)       { std::cout << "Search pointer is NULL\n"; return false;}
    if (*search == '\0')      { std::cout << "'\\0' string\n          "; return false;}
    
    if (flagSet_[0] == true)
    {
        while (strlen(search) > ind)
        {
            search[ind] = std::tolower(search[ind]);
            ++ind;
        }
    }
    search_ = search;
    return true;
}

/*
 -n, --line-number
 Each output line is preceded by its relative line number in the file, starting at line 1.  The line
 number counter is reset for each file processed.  This option is ignored if -c, -L, -l, or -q is
 specified.
 
 -l, --files-with-matches
 Only the names of files containing selected lines are written to standard output.  grep will only
 search a file until a match has been found, making searches potentially less expensive.  Pathnames
 are listed once per file searched.  If the standard input is searched, the string ``(standard
 input)'' is written.
 
 -i, --ignore-case
 Perform case insensitive matching.  By default, grep is case sensitive.
 
 -V, --version
 Display version information and exit.*/
 
