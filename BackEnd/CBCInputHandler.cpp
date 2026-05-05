#include <iostream>
#include <string>
#include "Language/CBCLanguage.cpp"

//on startup, select between active translation or file reading
///TODO: Live translation
///TODO: File reading
int main(){
    std::string userInput;
    CBC CBC;

    ///TODO: maybe add trim spaces

    while(true){
        //selection
        std::cout << "Select useage by entering number:" << "\n"
                << "0. Exit" << "\n"
                << "1. Live Translation" << "\n"
                << "2. Read File" 
                    << std::endl;

        std::getline(std::cin, userInput);
        if (userInput == "0"){
            exit(0);
        } else if (userInput == "1"){
            std::cout << "This usage has not been implemented, terminating program.";

        } else if (userInput == "2") {
            std::cout << "input file name:";
            std::getline(std::cin, userInput);

            CBC.runFile(userInput); // send file name to language
        } else {
            std::cout << "invalid input detected, please try again." << std::endl;
        }
    }
}