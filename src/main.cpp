#include "main.hpp"
#include "audio.hpp"
#include "event.hpp"
#include "figure.hpp"
#include "physical.hpp"
#include "libheader.hpp"
#include <memory>

SDL_Window *p_win;
SDL_Renderer *renderer;
SDL_Texture* texture;
int width = 1920;
int height = 1080;
int fps = 60;

int physical(){
    return crash();
}

int draw_back(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 1;
}

void _move(int key){
    player_move(key);
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
    player_init();
    audio_init();
    return 1;
}


int draw(){
    draw_back();
    SDL_RenderClear(renderer);
    for(int i = 0; i < enemy_cnt; ++i){
        item &e = ret_enemy(i);
        e.frame_cnt(fps * 0.5);
        SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer, e.ret_img());
        SDL_RenderCopyEx(renderer, texture, 0, e.ret_rect(), e.ret_angle(), 0, SDL_FLIP_NONE);
    }
    SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, ret_player().ret_img());
    SDL_RenderCopyEx(renderer, texture, 0, ret_player().ret_rect(), ret_player().ret_angle(), 0, SDL_FLIP_NONE);
    enemy_move();
    SDL_RenderPresent(renderer);
    return 1;
}

int quit_game(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(p_win);
    free_img();
    free_audio();
    return 1;
}

int start_game() {
    init_game();
    event_monitor();
    quit_game();
    return 1;
}

int again(){
    for(int i = 0; i < enemy_cnt; ++i)
        enemy_move_init(i);
    return event_again();;
}

int run(){
    draw();
    audio_check();
    if(!physical()){
        //audio_over();
        return again();
    }
    return 2;
}