
#include "xstring.h"
#include <iostream>
#include "grep.h"
#include "nfa.h"
#include "vector.h"
#include <fstream>

typedef std::string fstring;
typedef fsu::Vector<String> FileVector;
typedef fsu::Vector<Vector> FilesVector;

void GrepHelp();
void CommandFormat();

//test
int main(int argc, char* argv[])
{
    
    //format of grep command
    //GREP.x [flags] [pattern] [inFile] [outFile]
    fstring help = "-help";
    // Error
    if (argc == 3)
    {
        std::ifstream file(argv[2]);
        if (file.fail())
        {
            std::cout << argv[2] << " file does not exist ";
            std::cout << std::endl;
            return 1;
        }
    }
    if (argc == 1){
        CommandFormat();
        return 1;
    }
    if (help.compare(argv[1]) == 0)
    {
        std::cout<< "help arguments";
        GrepHelp();
        return 1;
    }
    

	std::cout << "I did a thing! "<< argv[1] << " "<< argv [2] << "\n";
    fstring str;
    
    
    return 1;
}
void GrepHelp()
{
    // Implementation according to flags
    std::cout << "Regexp selection and interpretation:"
              << "\n -E, --extended-regexp     PATTERN is an extended regular expression "
              << "\n -F, --fixed-strings       PATTERN is a set of newline-separated strings ";

    std::cout << std::endl;
}
void CommandFormat()
{
    std::cout << "grep.x [flags] [pattern] [inFile] [outFile]"
              << std::endl;
}