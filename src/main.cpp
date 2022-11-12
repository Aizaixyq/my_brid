#include "main.hpp"
#include "event.hpp"
#include <libheader.hpp>

SDL_Window *p_win;
SDL_Surface *p_screen;
int width = 400;
int height = 300;

int create_win() {
    auto win =
        SDL_CreateWindow("brid_dev", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    p_win = win;
    if (win == nullptr) {
        fmt::print("detail: {}", SDL_GetError());
        return 0;
    }
    return 1;
}

int draw_back(){
    auto scr = SDL_GetWindowSurface(p_win);
    p_screen = scr;
    SDL_Rect back = {0, 0, width, height};
    SDL_FillRect(p_screen, &back, 0xffffffff);
    SDL_UpdateWindowSurface(p_win);
    return 1;
}

int start_game() {
    create_win();
    draw_back();
    event_monitor();
    return 1;
}
