#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "Categories.cpp"

class CBC {
    private:
        std::unordered_map<int, std::string> env;
        Category cat;

        //used to trim extra spaces
        std::string trim(const std::string& str) {
            auto start = str.begin();
            while (start != str.end() && std::isspace(*start)) ++start;
            auto end = str.end();
            do { --end; } while (end != start && std::isspace(*end));
            return std::string(start, end + 1);
        }
        template <typename T>
        std::string toString(const T& value) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }

        //translate raw inputs into readable language
        std::string translate(std::string input){
            return toString(cat.getCat(input[0],input.substr(1)));
        }

        std::string run(std::string input) {
            std::string translatedLine = "";
            while(!input.empty()) {
                
                // Handle leading spaces
                if (std::isspace(input.front())) {
                    input.erase(0, 1);
                    continue;
                }

                // Translate 4-character tokens :'''###'
                if (input.length() >= 4) { 
                    translatedLine.append(translate(input.substr(0, 4)));
                    input.erase(0, 4);
                } else {
                    input.clear();
                }
            }
            return translatedLine;
        }

    public:
        void runLive(){
            //should handle live translation of controller input
            ///TODO: take input from controller handler
            ///TODO: translate input using run() or translate()
            ///TODO: output as live keyboard input
            //example: n045 would be translated to 1, then output as if the user typed "1" on the keyboard
            //example: c300 would be translated to "if ", then output as if the user typed "if " on the keyboard
            std::cout << "This usage has not been implemented.";
        }
        void runFile(std::string fileName){
            std::ifstream fileIn(fileName);
            
            if (!fileIn.is_open()) {
                std::cerr << "Error: Could not open " << fileName <<"." << std::endl;
                exit(1);
            }

            ///TODO: replace ".cpp" with input from controller handler to select any language
            fileName = fileName.substr(0, fileName.find_last_of('.')) + ".cpp";
            std::ofstream fileOut;
            fileOut.open(fileName, std::ios::out);

            std::string line;
            //loop each line in file till end of file
            while (std::getline(fileIn, line)){
                fileOut << run(trim(line)) << std::endl;
            }
            fileIn.close();
            fileOut.close();

            ///TODO: add to dump the files with the inputfile location
            //Compiles a .exe to run the file output
            std::string compile = "cl \"" + fileName + "\"";
            if (system(compile.c_str()) != 0) {
                std::cerr << "Compile failed." << std::endl;
                exit(1);
            }
            //executes .exe
            system((".\\" + fileName.substr(0, fileName.find_last_of('.')) + ".exe").c_str());
        }
};