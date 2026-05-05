#include <string>
#include <variant>
class Category{
    private:
        const int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const char abc[12] = {'a', 'b'  , 'c', 'x'  , 'y'  , 'z'  , 'A'  , 'B'  , 'C', 'X'  , 'Y'  , 'Z'};
        const char equation[7] = {'='  , '+'  , '-'  , '*'  , '/'  , '(', ')' };
        const char special[26] = {' ', '!', '/', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '\"', ',', '.', '?'};
        const std::string cond[3] = {"if ()"  , "else"  , "else if ()"};
        const std::string loop[3] = {"for ()", "while ()", "Do {} while ()"};
        const std::string TEMPNAME[4] =  {"{}"  , "()"  , "\"\""  , "[]" };

    public:
        using Var = std::variant<int, char, std::string>;

        Var getCat(char ident, std::string degree) {
            int select = std::stoi(degree) * 10 / 360; // convert degree to a number to pick from a catagory
            //select which catagory to use
            switch (ident){
                case 'n': 
                    if (select >= 10) select = 9; 
                    return num[select];
                case 'a': 
                    if (select >= 12) select = 11; 
                    return abc[select];
                case 'e': 
                    if (select >= 7) select = 6; 
                    return equation[select];
                case 's': 
                    if (select >= 26) select = 25; 
                    return special[select];
                case 'c': 
                    if (select >= 3) select = 2; 
                    return cond[select];
                case 'l': 
                    if (select >= 3) select = 2; 
                    return loop[select];  
                case 'T': 
                    if (select >= 4) select = 3; 
                    return TEMPNAME[select];
                default: 
                    std::cerr << "Error: Catagory does not exist";
            }
        }
};