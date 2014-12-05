

#include "vector.h"
#include <string>
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
    bool   search     (const char* search);
private:
    bool   flagSet_[10];
    Vector results_;
    Vector flag_;
    const char * search_ = NULL;
    
};

Grep::Grep()
{
    for(size_t ctr = 0; ctr < 10; ++ctr )
        flagSet_[ctr] = false;
}

bool Grep::setFlag(const char* flagSet)
{
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
            std::cout << "Load Failed\n";
            return 0;
        }
        
        if (search_ == NULL) {
            std::cout << "Search parameter not set\n";
        }
        Nfa nfa(search_);
        while (!inStream.eof())
        {
            std::getline(inStream,line,'\n');
            ++lineNumber;
            
            if( nfa.Matches( line.c_str() ) )
            {
                //if flag set add line number to front of line
                results_.PushBack(line);
            }
           
            line.clear();
        }
        
    }
    return true;
}

Vector Grep::results()
{
    return results_;
}

bool Grep::search(const char* search)
{
    if (sizeof(*search) == 0) { std::cout << "Search is zero\n"; return false;}
    if (search == NULL)       { std::cout << "Search is zero\n"; return false;}
    if (*search == '\0')      { std::cout << "'\\0' string\n  "; return false;}
    
    std::cout << "search = " << search << '\n';
    if (search == NULL) return false;
    search_ = search;
    return true;
}
