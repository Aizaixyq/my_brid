#include "event.hpp"
#include "main.hpp"
#include "libheader.hpp"

// event monitor
int event_monitor() {
    while (true) {
        auto begin = SDL_GetTicks();
        draw();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
#ifdef DEBUG_EVENT
            fmt::print("event type:{}\n", event.type);
#endif
            if (event.type == SDL_QUIT)
                return 1;
        }
        auto end = SDL_GetTicks();
        auto cost = end - begin;
        auto frame = 1000 / fps;
        auto d = frame - cost;
        if(d < 0)d = 0;
        SDL_Delay(d);
    }
    return 0;
}