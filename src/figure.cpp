#include "figure.hpp"
#include "items.hpp"
#include "main.hpp"
#include "libheader.hpp"
#include <random>
#include <ctime>

const int enemy_cnt = 30;
int wp, hp;
std::vector<std::pair<int, int>> enemies(enemy_cnt * 2);
// 创建整型随机数分布器，生成指定范围内的随机数
std::uniform_int_distribution<int> dis_x;
std::uniform_int_distribution<int> dis_y;
std::uniform_int_distribution<int> dis_dir;
std::uniform_int_distribution<int> dis_step;

item player, enemy;
item _enemy[enemy_cnt];

SDL_Surface *img;
SDL_Surface *img1;
SDL_Surface *img2;
SDL_Surface *img3;

item& ret_enemy(int index){
    return _enemy[index];
}

item& ret_player(){
    return player;
}


// 生成敌人位置和路线的函数
// 输入参数：
//     width: 程序窗口宽度
//     height: 程序窗口高度
//     enemy_cnt: 敌人个数
// 输出参数：
//     enemies: 生成的敌人位置和路线
void random_enemy(int enemy_index, std::vector<std::pair<int, int>>& enemies) {

    // 生成随机数种子
    std::random_device rd;
    // 创建随机数生成器
    std::mt19937 gen(rd());
    // 生成敌人位置和路线
    if (enemy_index > -1 && enemy_index < enemy_cnt) {
        // 计算敌人位置
        int x = 0, y = 0;
        switch (dis_dir(gen)) {
        case 0:
            x = -wp;
            y = dis_y(gen);
            break;
        case 1:
            x = dis_x(gen);
            y = -hp;
        case 2:
            x = width + wp;
            y = dis_y(gen);
            break;
        case 3:
            x = dis_x(gen);
            y = height + hp;
            break;
        }

        // 计算敌人路线
        int dx = dis_step(gen);
        int dy = dis_step(gen);

        // 将敌人位置和路线保存到列表中
        enemies[enemy_index] = std::make_pair(x, y);
        enemies[enemy_index + enemy_cnt] = std::make_pair(dx, dy);
        //update location
        _enemy[enemy_index].update_loc(x, y);
        if(dx == 0 && dy == 0){
            dx = 3;
            enemies[enemy_index + enemy_cnt] = std::make_pair(dx, dy);
            _enemy[enemy_index].ret_angle() = 0;
        }
        if(dx > 0 && dy > 0){
            _enemy[enemy_index].ret_angle() = 45;
        }
        else if(dx > 0 && dy < 0){
            _enemy[enemy_index].ret_angle() = -45;
        }
        else if(dx < 0 && dy > 0){
            _enemy[enemy_index].ret_angle() = 135;
        }
        else if(dx < 0 && dy < 0){
            _enemy[enemy_index].ret_angle() = -135;
        }
        else if(dx == 0 && dy < 0){
            _enemy[enemy_index].ret_angle() = -90;
        }
        else if(dx == 0 && dy > 0){
            _enemy[enemy_index].ret_angle() = 90;
        }
        else if(dx < 0 && dy == 0){
            _enemy[enemy_index].ret_angle() = -180;
        }
    }
}


void enemy_move_init(int i){
    _enemy[i].frame_cnt(-1);
    random_enemy(i, enemies);
}


void enemy_move(){
    int x, y, w, h;
    auto r = enemy.ret_rect();
    w = r->w;
    h = r->h;
    for(int i = 0; i < enemy_cnt; ++i){
        r = _enemy[i].ret_rect();
        x = enemies[i + enemy_cnt].first + r->x;
        y = enemies[i + enemy_cnt].second + r->y;
        _enemy[i].update_loc(x, y);
        if(x > width + wp || x < -wp || y > height + hp || y < -hp){
            enemy_move_init(i);
        }
    }
}
void _move1(int key){
    auto a = player.ret_rect();
    switch (key) {
        case SDLK_a:
            player.update_loc(a->x - 20, a->y);
            break;
        case SDLK_d:
            player.update_loc(a->x + 20, a->y);
            break;
        case SDLK_w:
            player.update_loc(a->x, a->y - 20);
            break;
        case SDLK_s:
            player.update_loc(a->x, a->y + 20);
            break;
        default:
            _move(key);
            break;
    }
}

void player_move(int key){
    auto a = player.ret_rect();
    switch (key) {
        case SDLK_LEFT:
            player.update_loc(a->x - 20, a->y);
            break;
        case SDLK_RIGHT:
            player.update_loc(a->x + 20, a->y);
            break;
        case SDLK_UP:
            player.update_loc(a->x, a->y - 20);
            break;
        case SDLK_DOWN:
            player.update_loc(a->x, a->y + 20);
            break;
        default:
            _move1(key);
            break;
    }
}


void player_init(){
    img = IMG_Load("art/playerGrey_up1.png");
    img1 = IMG_Load("art/playerGrey_up2.png");
    img2 = IMG_Load("art/playerGrey_walk1.png");
    img3 = IMG_Load("art/playerGrey_walk2.png");
    player.add_img(img);
    player.add_img(img1);
    player.add_img(img2);
    player.add_img(img3);
    player.update_loc(width/2, height/2);
    player.switch_img();
}

void enemy_init(){
    img = IMG_Load("art/enemySwimming_1.png");
    img1 = IMG_Load("art/enemySwimming_2.png");
    enemy.add_img(img);
    enemy.add_img(img1);
    enemy.update_loc(width, height);
    enemy.switch_img();
    wp = enemy.ret_rect()->w + 20;
    hp = enemy.ret_rect()->h + 20;
    dis_x = std::uniform_int_distribution<int> (-wp, width + wp);
    dis_y = std::uniform_int_distribution<int> (-hp, height + hp);
    dis_dir = std::uniform_int_distribution<int> (0, 3);
    dis_step = std::uniform_int_distribution<int> (-2, 2);
    for(int i = 0; i < enemy_cnt; ++i){
        _enemy[i] = enemy;
        enemy_move_init(i);
    }
}

void free_img(){
    SDL_FreeSurface(img);
    SDL_FreeSurface(img1);
    SDL_FreeSurface(img2);
    SDL_FreeSurface(img3);
}