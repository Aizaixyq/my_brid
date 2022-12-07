#include "items.hpp"
#include "libheader.hpp"

item::item(): x(0), y(0), w(0), h(0), ptr(-1), frame_ctr(0), angle(0){}

item::item(item &x): x(x.x), y(x.y), w(x.w), h(x.h), ptr(x.ptr), img(x.img), angle(x.angle), frame_ctr(0){}

item::~item(){}

void item::operator = (item &x){
    this->x = x.x;
    this->y = x.y;
    this->w = x.w;
    this->h = x.h;
    this->ptr = x.ptr;
    this->frame_ctr = x.frame_ctr;
    this->img = x.img;
    this->angle = x.angle;
}

void item::add_img(SDL_Surface *s){
    img.emplace_back(s);
}

void item::update_loc(int _x, int _y){
    x = _x;
    y = _y;
}

void item::switch_img(){
    ++ptr;
    if(ptr >= img.size()){
        ptr = 0;
    }
    w = img[ptr]->w;
    h = img[ptr]->h;
}

void item::point_img(int p){
    ptr = p;
    if(ptr >= img.size() && ptr < 0){
        ptr = 0;
    }
    w = img[ptr]->w;
    h = img[ptr]->h;
}

SDL_Rect* item::ret_rect(){
    r = {x, y, w, h};
    return &r;
}

SDL_Surface* item::ret_img(){
    return img[ptr];
}

double& item::ret_angle(){
    return angle;
}

void item::frame_cnt(int flag){
    ++frame_ctr;
    if(flag < 0){
        point_img(0);
        frame_ctr = 0;
    }
    else if(frame_ctr > flag){
        switch_img();
        frame_ctr = 0;
    }
    //fmt::print("{}\n", frame_ctr);
}