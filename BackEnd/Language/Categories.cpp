#include <iostream>
#include <string>
#include <variant>
class Category{
    private:
        /// NOTE: update/check "BackEnd/ControllerHandler/CInputToCBC.cpp" if any changes happen here
        const int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const char abc[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                              'n','o','p','q','r','s','t','u','v','w','x','y','z'};
        const char ABC[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                              'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        const char equation[7] = {'='  , '+'  , '-'  , '*'  , '/'  , '(', ')' };
        const char special[26] = {' ', '!', '/', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', 
                                  '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '\"', ',', '.', '?'};
        const std::string cond[3] = {"if ", "else", "else if "};
        const std::string loop[3] = {"for", "while", "Do"}; // for live, not for file
        const std::string TEMPNAME[4] =  {"{}"  , "()"  , "\"\""  , "[]"}; // for live, not for file
        const char TEMPNAME2[10] =  {'{', '}', '(', ')', '\"', '\"', '[', ']'}; 
    public:
        using Var = std::variant<int, char, std::string>;

        Var getCat(char ident, std::string degree) {
            //identify which catagory to use
            //select from catagory from degrees conversion
            //if overflow, reduce to last in catagory
            switch (ident){
                case 'n': 
                    int select = std::stoi(degree) * 10 / 360;
                    if (select >= 10) select = 9; 
                    return num[select];
                case 'a': 
                    int select = std::stoi(degree) * 26 / 360;
                    if (select >= 26) select = 25; 
                    return abc[select];
                case 'A': 
                    int select = std::stoi(degree) * 26 / 360;
                    if (select >= 26) select = 25; 
                    return ABC[select];
                case 'e': 
                    int select = std::stoi(degree) * 7 / 360;
                    if (select >= 7) select = 6; 
                    return equation[select];
                case 's': 
                    int select = std::stoi(degree) * 26 / 360;
                    if (select >= 26) select = 25; 
                    return special[select];
                case 'c': 
                    int select = std::stoi(degree) * 3 / 360;
                    if (select >= 3) select = 2; 
                    return cond[select];
                case 'l': 
                    int select = std::stoi(degree) * 3 / 360;
                    if (select >= 3) select = 2; 
                    return loop[select];  
                case 'T': 
                    int select = std::stoi(degree) * 4 / 360;
                    if (select >= 4) select = 3; 
                    return TEMPNAME[select];
                case 'z': 
                    int select = std::stoi(degree) * 10 / 360;
                    if (select >= 10) select = 9; 
                    return TEMPNAME2[select];
                default: 
                    std::cerr << "Error: Category does not exist";
                    exit(1);
            }
        }
};