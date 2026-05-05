#include <SDL3/SDL.h>
#include <iostream>

int main() {
    //initalize SDL
    if (!SDL_Init(SDL_INIT_GAMEPAD)) {
        std::cerr << "SDL init failed: " << SDL_GetError() << "\n";
        exit(1);
    }
    
    // count of controllers visable
    int count = 0; 
    SDL_JoystickID* gamepads = SDL_GetGamepads(&count);
    // if any controllers exist
    if (!gamepads || count == 0) {
        std::cout << "No controller found\n";
        SDL_free(gamepads);
        SDL_Quit();
        exit(1);
    }

    //use first controller
    SDL_Gamepad* controller = SDL_OpenGamepad(gamepads[0]);
    SDL_free(gamepads);

    //check if controlle = usable
    if (!controller) {
        std::cerr << "Could not open controller: " << SDL_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }

    SDL_Event e;
    while (true) {
        //process each input from controller live
        while (SDL_PollEvent(&e)) {
            //buttons
            if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
                std::cout << "Button: " << (int)e.gbutton.button << "\n";
            }
            //thumbsticks/joysticks
            if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                std::cout << "Axis: " << (int)e.gaxis.axis
                          << " value: " << e.gaxis.value << "\n";
            }
            //when window is closed
            if (e.type == SDL_EVENT_QUIT) {
                SDL_CloseGamepad(controller);
                SDL_Quit();
                exit(0);
            }
        }
    }
}