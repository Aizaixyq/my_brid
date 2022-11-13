#include "main.hpp"
#include "libheader.hpp"

extern SDL_Window *p_win;

int main() {
    int state;
    state = SDL_Init(SDL_INIT_EVERYTHING);
    if (!state) {
        fmt::print("startup error\n");
        fmt::print("detail: {}\n", SDL_GetError());
        return 1;
    }

    start_game();
    SDL_DestroyWindow(p_win);
}