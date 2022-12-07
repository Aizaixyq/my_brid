#include "figure.hpp"
#include "libheader.hpp"


int crash(){
    auto p = ret_player();
    auto e = ret_player();
    for(int i = 0; i < enemy_cnt; ++i){
        e = ret_enemy(i);
        if(SDL_HasIntersection(p.ret_rect(), e.ret_rect())){
            return 0;
        }
    }
    return 1;
}