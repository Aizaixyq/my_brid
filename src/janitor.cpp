#include "main.hpp"
#include "libheader.hpp"


int main() {
    int state;
    state = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | 
        SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | 
        SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
    if (state) {
        fmt::print("startup error:{}\n", state);
        fmt::print("detail: {}\n", SDL_GetError());
        return 1;
    }

    start_game();
    SDL_Quit();
}