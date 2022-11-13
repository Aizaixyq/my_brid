#include "event.hpp"
#include "libheader.hpp"

// event monitor
int event_monitor() {
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
#ifdef DEBUG_EVENT
            fmt::print("event type:{}\n", event.type);
#endif
            if (event.type == SDL_QUIT)
                return 1;
        }
    }
    return 0;
}