
#include "xstring.h"
#include <fstream>
#include <iostream>
#include "grep.h"
#include "nfa.h"

typedef std::string            String;
typedef fsu::Vector<String>    Vector;
//test
int main(int argc, char* argv[])
{
    Vector filenames;
    //format of grep command
    //GREP.x [flags] [pattern] [inFile] [outFile]

    Grep gp;
    std::string string;
    char * array;
    
    filenames.PushBack("movies_test.txt");
    //filenames.PushBack("file 2.txt");
    //filenames.PushBack("file 3.txt");
    
    if(!gp.search(array))
        std::cout << "Search failed\n";
    else
    {
        gp.processing(filenames);
        if (gp.search(NULL))
        {
        std::cout << "Search Invalid\n";
        }
    }
    
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