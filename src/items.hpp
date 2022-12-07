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


/*// 创建旋转图片的函数
SDL_Surface* rotateSurface(SDL_Surface* src, int angle) {
    // 计算旋转后图片的大小
    int w, h;
    if (angle == 90 || angle == 270) {
        w = src->h;
        h = src->w;
    }
    else {
        w = src->w;
        h = src->h;
    }

    // 创建一个新的旋转后图片的Surface
    SDL_Surface* rotatedSurface = SDL_CreateRGBSurface(0, w, h,
        src->format->BitsPerPixel, src->format->Rmask,
        src->format->Gmask, src->format->Bmask, src->format->Amask);
    if (rotatedSurface == NULL) {
        std::cerr << "SDL_CreateRGBSurface failed: " << SDL_GetError() << std::endl;
        return NULL;
    }

    // 旋转图片
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);
    if (SDL_BlitSurface(src, NULL, rotatedSurface, NULL) != 0) {
        std::cerr << "SDL_BlitSurface failed: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_SetSurfaceRotation(rotatedSurface, angle);

    return rotatedSurface;
}*/

#endif