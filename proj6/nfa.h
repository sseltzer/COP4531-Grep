

#include <string>

class Nfa
{
public:
         Nfa     (const char* search);
    bool Matches (const char * line);
    
private:
    char * postfixPattern_;
};

Nfa::Nfa(const char* pattern)
{
    //std::cout << "Search is " << pattern << '\n';
    
    //start by first char in pattern = root node
    //build tree
    //while(pattern not empty)
    //{
        //if '(' add_left_node
    
        //if ')' add_left_node
    
        //if '*' add_left_node
    
        //if '|'
        //{
            //search for first parent_node = '('
            //temp_node = parent_node
            // 
}
bool Nfa::Matches(const char * line)
{
    //std::cout << line << '\n';
    return true;
}



//prefix search string
//make tree
