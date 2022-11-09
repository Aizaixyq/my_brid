#include "main.hpp"
#include "event.hpp"
#include <libheader.hpp>

SDL_Window *p_win;

int create_win() {
    auto win =
        SDL_CreateWindow("pvz_dev", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);
    p_win = win;
    if (win == nullptr) {
        fmt::print("detail: {}", SDL_GetError());
        return 0;
    }
    return 1;
}

int start_game() {
    create_win();
    event_monitor();
    return 1;
}
