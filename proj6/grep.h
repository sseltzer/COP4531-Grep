

#include "vector.h"
#include <string>

typedef std::string            String;
typedef fsu::Vector<String>    Vector;



typedef size_t            Flag;

class Grep
{
public:
    Grep            ();
    bool setFlag    (const char* flag);
    void input      (Vector input);
    void output     (Vector output);
    void search     (Vector search);
private:
    char* flag_;
    Vector string_;
    
};

Grep::Grep()
{
    
}

bool Grep::setFlag(const char* flag)
{
    return true;
}

void Grep::input (Vector input)
{
    
    
}

void Grep::output (Vector output)
{
    
}

void Grep::search(Vector search)
{
    
}
