#include "main.hpp"
#include "event.hpp"
#include "figure.hpp"
#include "libheader.hpp"
#include <memory>

SDL_Window *p_win;
SDL_Renderer *renderer;
SDL_Texture* texture;
int width = 800;
int height = 600;
int fps = 60;

int draw_back(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 1;
}

int init_game() {
    auto win =
        SDL_CreateWindow("dev", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    p_win = win;
    if (win == nullptr) {
        fmt::print("detail: {}", SDL_GetError());
        return 0;
    }

    auto render = SDL_CreateRenderer(p_win, -1, 0);
    renderer = render;
    if (!render) {
        // 如果创建渲染器失败，打印错误信息并退出程序
        fmt::print("SDL create renderer failed: {}\n", SDL_GetError());
        return 1;
    }

    draw_back();
    enemy_init();
    return 1;
}


int draw(){
    draw_back();
    SDL_RenderClear(renderer);
    for(int i = 0; i < 5; ++i){
        auto e = _enemy[i];
        texture = SDL_CreateTextureFromSurface(renderer, e.ret_img());
        SDL_RenderCopy(renderer, texture, 0, e.ret_rect());
    }
    enemy_move();
    SDL_RenderPresent(renderer);
    return 1;
}

int quit_game(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(p_win);
    free_img();
    return 1;
}

int start_game() {
    init_game();
    event_monitor();
    quit_game();
    return 1;
}
