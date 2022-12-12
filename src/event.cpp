#include "event.hpp"
#include "main.hpp"
#include "libheader.hpp"

// event monitor
int event_monitor() {
    SDL_Event event;
    while (true) {
        int begin = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
#ifdef DEBUG_EVENT
            fmt::print("event type:{}\n", event.type);
#endif
            if (event.type == SDL_QUIT)
                return 1;
            else if(event.type == SDL_KEYDOWN){
                int key = event.key.keysym.sym;
                if(key >= 1073741903 && key <= 1073741906)
                    _move(key);
                else if(key == SDLK_w
                        || key == SDLK_a
                        || key == SDLK_s
                        || key == SDLK_d){
                    _move(key);
                }
            }
        }
        if(run() == 1){
            return 1;
        }
        int end = SDL_GetTicks();
        int cost = end - begin;
        int frame = 1000 / fps;
        int d = frame - cost;
        if(d < 0)d = 0;
        SDL_Delay(d);
    }
    return 0;
}

int event_again(){
    SDL_Event event;
    while (true) {
        int begin = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
#ifdef DEBUG_EVENT
            fmt::print("event type:{}\n", event.type);
#endif
            if (event.type == SDL_QUIT)
                return 1;
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_MouseButtonEvent* mouseEvent = (SDL_MouseButtonEvent*)&event;
                if (mouseEvent->button == SDL_BUTTON_LEFT) {
                    return 2;
                }
            }
        }
        int end = SDL_GetTicks();
        int cost = end - begin;
        int frame = 1000 / fps;
        int d = frame - cost;
        if(d < 0)d = 0;
        SDL_Delay(d);
    }
    return 0;
}