#include "main.hpp"
#include "libheader.hpp"


int main() {
    int state;
    state = SDL_Init(SDL_INIT_EVERYTHING);
    if (!state) {
        fmt::print("startup error\n");
        fmt::print("detail: {}\n", SDL_GetError());
        return 1;
    }

    start_game();
    SDL_Quit();
}