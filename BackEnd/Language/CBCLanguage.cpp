#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "Catagories.h"

class CBC {
    private:
        std::unordered_map<int, std::string> env;

        //used to trim extra spaces
        std::string trim(const std::string& str) {
            auto start = str.begin();
            while (start != str.end() && std::isspace(*start)) ++start;
            auto end = str.end();
            do { --end; } while (end != start && std::isspace(*end));
            return std::string(start, end + 1);
        }

        //translate raw inputs into readable language
        std::string translate(std::string input){
            
            num[2];

        }
        void run(std::string input){
            input = translate(input);


        }

    public:
        void runLive(){

        }
        void runFile(std::string fileName){
            std::ifstream file(fileName);
            
            if (!file.is_open()) {
                std::cerr << "Error: Could not open " << fileName <<"." << std::endl;
                return;
            }

            std::string line;
            //loop each line in file till end of file
            while (std::getline(file, line)){
                run(trim(line));
            }

            file.close();
            return;
        }
};