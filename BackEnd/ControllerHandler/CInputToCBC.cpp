#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <SDL3/SDL.h>
#include "Language/Categories.cpp"
#include "Language/CBCLanguage.cpp"

///TODO: just double check, as enter is loaded with being the enter key, and also confirm button
///FIXME:handleButtonPress() uses endl, others use flush, should be consistent, flush is better for live updates so changing to that.
class CInputToCBC {
    std::string trim(const std::string& s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = s.find_last_not_of(" \t\r\n");
        return s.substr(first, (last - first + 1));
    }

private:
    // Maps physical SDL buttons to their assigned categories
    std::unordered_map<int, std::vector<char>> buttonConfigs;
    
    // Tracks current state for the action wheel
    int currentCatIdx = 0;
    int currentDegree = 0;
    int activeSdlButton = -1; 
    
    const int DEADZONE = 8000; // Joystick threshold 

public:
    // Reads text settings and converts them to usable backend arrays
    ///TODO: changing to use a YAML file for settings instead of custom text format, will require a YAML parser library
    void loadSettings(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open " << filename << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.find("Button") == 0) {
                size_t colonPos = line.find(":");
                if (colonPos == std::string::npos) continue;

                int btnNum = std::stoi(line.substr(7, colonPos - 7));
                int sdlIdx = btnNum - 1; 

                std::string catsPart = line.substr(colonPos + 1);
                std::stringstream ss(catsPart);
                std::string segment;
                std::vector<char> parsedCats;

                while (std::getline(ss, segment, ',')) {
                    segment = trim(segment);
                    if (segment == "number") parsedCats.push_back('n');
                    else if (segment == "abc") parsedCats.push_back('a');
                    else if (segment == "equation") parsedCats.push_back('e');
                    else if (segment == "special") parsedCats.push_back('s');
                    else if (segment == "cond") parsedCats.push_back('c');
                    else if (segment == "loop") parsedCats.push_back('l');
                    else if (segment == "TEMPNAME") parsedCats.push_back('T');
                }
                buttonConfigs[sdlIdx] = parsedCats; 
            }
        }
    }

 // Fix Up = 0°
void updateJoystick(int16_t x, int16_t y) {
    if (std::abs(x) > DEADZONE || std::abs(y) > DEADZONE) {
        // Swapping x and y, and negating y 
        // helps align 0 with the top of the circle
        double radians = std::atan2(static_cast<double>(x), static_cast<double>(-y));
        double degrees = radians * (180.0 / 3.14159265);
        
        // Ensure result is within 0-360
        if (degrees < 0) degrees += 360.0;
        
        currentDegree = static_cast<int>(degrees);
        displayUI();
    }
}
    // Combines the active category prefix with the 3-digit joystick degree
    // Makes sure the output matches the required CBC syntax format
    std::string getConfirmedToken() {
        if (activeSdlButton == -1) return "";

        char catPrefix = buttonConfigs[activeSdlButton][currentCatIdx];
        std::stringstream ss;
        // Apply zero-padding to keep the degree exactly 3 characters long
        ss << catPrefix << std::setw(3) << std::setfill('0') << currentDegree;
        return ss.str();
    }

    //Controller Actions Buttons, Spacebar, Enter 
    ///FIXME: cbcProcessor.run() showing a error on my end
    ///TODO: make sure these inputs are not hard coded to a button but from the selected button in settings file.
    void handleButtonPress(int sdlButtonIdx, CBC& cbcProcessor) {
        // Spacebar Action Immediately sends 's000' 
        if (sdlButtonIdx == SDL_GAMEPAD_BUTTON_LEFT_SHOULDER) { // Mapping LB1 to Space[cite: 6]
            std::cout << "\n[ACTION: Spacebar]" << std::endl;
            cbcProcessor.run("s000"); // 's000' represents a space ' '[cite: 1, 7].
            return;
        }

        //Mapped to Button 3 (X/Square)
        if (sdlButtonIdx == SDL_GAMEPAD_BUTTON_WEST) {
            std::cout << "\n[ACTION: Backspace]" << std::endl;
            return;
        }

        //Mapped to Button 2 (B/Circle)
        if (sdlButtonIdx == SDL_GAMEPAD_BUTTON_EAST) {
            std::string token = getConfirmedToken();
            if (!token.empty()) {
                std::cout << "\nConfirmed: " << token << std::endl;
                cbcProcessor.run(token);[cite: 3]
            }
            return;
        }

        // Cycle through categories on this button
        if (buttonConfigs.count(sdlButtonIdx)) {
            if (activeSdlButton == sdlButtonIdx) {
                currentCatIdx = (currentCatIdx + 1) % buttonConfigs[sdlButtonIdx].size();
            } else {
                activeSdlButton = sdlButtonIdx;
                currentCatIdx = 0;
            }
            displayUI();
        }
    }

    // Left Joystick handle: Move up, down, left, right around text
    void handleMovement(int16_t x, int16_t y) {
        if (std::abs(y) > DEADZONE) {
            if (y < 0) std::cout << "\r[NAV: Up]   " << std::flush;
            else std::cout << "\r[NAV: Down] " << std::flush;
        }
        if (std::abs(x) > DEADZONE) {
            if (x < 0) std::cout << "\r[NAV: Left] " << std::flush;
            else std::cout << "\r[NAV: Right]" << std::flush;
        }
    }

    void displayUI() {
        if (activeSdlButton == -1) return;
        char cat = buttonConfigs[activeSdlButton][currentCatIdx];
        std::cout << "\r[PREVIEW: " << cat << std::setw(3) << std::setfill('0') << currentDegree 
                  << "] | Confirm with Enter (Button 2)    " << std::flush;
    }
};
