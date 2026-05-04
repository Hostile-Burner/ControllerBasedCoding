#include <string>
class Catagory{
    private:
        const int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const char abc[12] = {'a', 'b'  , 'c', 'x'  , 'y'  , 'z'  , 'A'  , 'B'  , 'C', 'X'  , 'Y'  , 'Z'};
        const char equation[7] = {'='  , '+'  , '-'  , '*'  , '/'  , '(', ')' };
        const char special[26] = {' ', '!', '/', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '\"', ',', '.', '?'};
        const std::string cond[3] = {"if ()"  , "else"  , "else if ()"};
        const std::string loop[3] = {"for ()", "while ()", "Do {} while ()"};
        const std::string TEMPNAME[4] =  {"{}"  , "()"  , "\"\""  , "[]" };

    public:
        int getNum(std::string degree) {
            int select = std::stoi(degree) * 10 / 360;
            if (select >= 10) select = 9;
            return num[select];
        }
        char getAbc(std::string degree) {
            int select = std::stoi(degree) * 12 / 360;
            if (select >= 12) select = 11;
            return abc[select];
        }
        char getEquation(std::string degree) {
            int select = std::stoi(degree) * 7 / 360;
            if (select >= 7) select = 6;
            return equation[select];
        }
        char getSpecial(std::string degree) {
            int select = std::stoi(degree) * 26 / 360;
            if (select >= 26) select = 25;
            return special[select];
        }
        std::string getCond(std::string degree) {
            int select = std::stoi(degree) * 3 / 360;
            if (select >= 3) select = 2;
            return cond[select];
        }
        std::string getLoop(std::string degree) {
            int select = std::stoi(degree) * 3 / 360;
            if (select >= 3) select = 2;
            return loop[select];
        }
        std::string getTEMPNAME(std::string degree) {
            int select = std::stoi(degree) * 4 / 360;
            if (select >= 4) select = 3;
            return TEMPNAME[select];
        }
};