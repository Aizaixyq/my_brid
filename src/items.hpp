#include <iostream>
#include "libheader.hpp"
#ifndef _ITEMS_H_
#define _ITEMS_H_ 1

class item{
private:
    int x;
    int y;
    int w;
    int h;
    int ptr;
    std::vector<SDL_Surface*> img;
    SDL_Rect r;
    double angle;
    int frame_ctr;
public:
    item();
    item(item &x);
    ~item();
    void add_img(SDL_Surface *s);
    void switch_img();
    void point_img(int p);
    void update_loc(int _x, int _y);
    SDL_Rect* ret_rect();
    SDL_Surface* ret_img();
    double& ret_angle();
    void operator = (item &x);
    void frame_cnt(int flag);
};

#endif