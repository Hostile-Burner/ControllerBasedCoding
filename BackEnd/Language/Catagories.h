#ifdef CAT_H
#define CAT_H

#include <string>
class CAT{
    private:
        const int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const char abc[12] = {'a', 'b'  , 'c', 'x'  , 'y'  , 'z'  , 'A'  , 'B'  , 'C', 'X'  , 'Y'  , 'Z'};
        const char equation[6] = {'='  , '+'  , '-'  , '*'  , '/'  , '()' };
        const char special[26] = {' ', '!', '/', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '\"', ',', '.', '?'};
        const std::string cond[3] = {"if ()"  , "else"  , "else if ()"};
        const std::string loop[3] = {"for ()", "while ()", "Do {} while ()"};
        const std::string TEMPNAME[4] =  {"{}"  , "()"  , "\"\""  , "[]" };


    public:
        
};
#endif