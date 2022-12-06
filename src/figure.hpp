#include "items.hpp"
#ifndef _FIGURE_H_
#define _FIGURE_H_ 1

extern const int enemy_cnt;
extern item _enemy[20];
extern item player;

void enemy_move();
void player_move(int key);
void player_init();
void enemy_init();
void free_img();

#endif