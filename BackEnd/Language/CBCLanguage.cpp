#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

class CBC {
    private:
    std::unordered_map<int, std::string> env;
    std::vector<std::string> nums = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    std::vector<std::string> eq = {"=", "+", "-", "*", "/", "()"};
    std::vector<std::string> cond = {"if ()", "else", "else if ()"};
    std::vector<std::string> special = {" ", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "{", "}", "[", "]", ";", ":", ",", ".", "?"};

    //used to trim extra spaces
    std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) ++start;
        auto end = str.end();
        do { --end; } while (end != start && std::isspace(*end));
        return std::string(start, end + 1);
    }

    std::string pickFromCircle(int degrees, const std::vector<std::string>& options) {
        if (options.empty()) return "";
        // Divide 360 degrees
        float segment = 360.0f / options.size();
        int index = std::floor(degrees / segment);

        //Clamp Index to prevent out of bounds at 360
        if (index >= options.size()) index = options.size() - 1;
        return options[index];
    }
    //translate raw inputs into readable language
    std::string translate(std::string input){
        if (input.empty()) return "";

        std::string result = "";
        // Process chunks likes c024
        for (size_t i = 0; i < input.length(); i+= 4) {
            char identity = input [i];
            int degrees = std::stoi(input.substr(i + 1, 3);

            switch (identity) {
                case 'n': //Numbers
                    result += pickFromCircle(degrees, nums);
                    break;
                case 'e': //Equations
                    result += pickFromCircle(degrees, eq);
                    break;
                case 'c': //Conditionals
                    result += pickFromCircle(degrees, cond);
                    break;
                case 's': // Special characters
                    result += pickFromCircle(degrees, special);
                    break;
                case 'a': //Variables (abc)
                    result += "a"; //Placehold for alphabet logic
                    break;
            }
        }
        return result;
    }
    void run(std::string input){
        std::string code = translate(input);
        std::cout<< "Translating Code: " << code << std::endl;
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
