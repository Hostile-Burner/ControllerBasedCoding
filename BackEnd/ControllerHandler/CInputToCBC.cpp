#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <SDL3/SDL.h>
#include "Categories.cpp"
#include "Language/CBCLanguage.cpp"

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
    void loadSettings(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open " << filename << std::endl;
            return;
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

    // Uses the Right Joystick to determine selection degree 
    // Uses atan2 to calculate the angle from raw X/Y axis data
    void updateJoystick(int16_t x, int16_t y) {
        if (std::abs(x) > DEADZONE || std::abs(y) > DEADZONE) {
            double radians = std::atan2(static_cast<double>(y), static_cast<double>(x));
            // Normalize result from radians to a positive 0-360 degree value[cite: 1, 11]
            double degrees = (radians * 180.0 / 3.14159265) + 180.0; 
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

    // Backspace, Enter, Navigation
    void handleButtonPress(int sdlButtonIdx, CBC& cbcProcessor) {
        // Handle Backspace (Mapped to Button 3 in ControllerLayout)
        if (sdlButtonIdx == SDL_GAMEPAD_BUTTON_WEST) {
            std::cout << "\n[ACTION: Backspace]" << std::endl;
            // TODO: Implementation for text deletion logic
            return;
        }

        // Handle Enter/Confirm Selection (Mapped to Button 2)
        if (sdlButtonIdx == SDL_GAMEPAD_BUTTON_EAST) {
            std::string token = getConfirmedToken();
            if (!token.empty()) {
                std::cout << "\nConfirmed Selection: " << token << std::endl;
                cbcProcessor.run(token); // Send to language engine[cite: 3]
            }
            return;
        }

        // Handle Category Cycling for mapped buttons
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

    // Left Joystick handle: Move up, down, left, right around text[cite: 4, 11]
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
