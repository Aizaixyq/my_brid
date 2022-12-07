#include "items.hpp"
#ifndef _FIGURE_H_
#define _FIGURE_H_ 1

extern const int enemy_cnt;

item& ret_enemy(int index);
item& ret_player();
void enemy_move();
void player_move(int key);
void player_init();
void enemy_init();
void free_img();

#endif