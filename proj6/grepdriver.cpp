
#include "xstring.h"
#include <iostream>
#include "grep.h"
#include "nfa.h"

//test
int main(int argc, char* argv[])
{
    
    //format of grep command
    //GREP.x [flags] [pattern] [inFile] [outFile]

	std::cout << "I did a thing! "<< argc << "\n";
    fsu::String str;
    
    
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