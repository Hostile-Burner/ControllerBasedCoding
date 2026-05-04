#include <SDL3/SDL.h>
#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_GAMEPAD)) {
        std::cout << "SDL init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    int count = 0;
    SDL_JoystickID* gamepads = SDL_GetGamepads(&count);

    if (count == 0) {
        std::cout << "No controller found\n";
        SDL_free(gamepads);
        SDL_Quit();
        return 1;
    }

    SDL_Gamepad* controller = SDL_OpenGamepad(gamepads[0]);
    SDL_free(gamepads);

    if (!controller) {
        std::cout << "Could not open controller: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
                std::cout << "Button: " << (int)e.gbutton.button << "\n";
            }

            if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                std::cout << "Axis: " << (int)e.gaxis.axis
                          << " value: " << e.gaxis.value << "\n";
            }

            if (e.type == SDL_EVENT_QUIT) {
                SDL_CloseGamepad(controller);
                SDL_Quit();
                return 0;
            }
        }
    }
}