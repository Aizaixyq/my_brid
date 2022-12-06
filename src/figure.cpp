#include "figure.hpp"
#include "items.hpp"
#include "main.hpp"
#include "libheader.hpp"
#include <random>
#include <ctime>

const int enemy_cnt = 20;
std::vector<std::pair<int, int>> enemies(enemy_cnt * 2);
item player, enemy;
item _enemy[enemy_cnt];
int enemy_loc[enemy_cnt][5];
int wp, hp;
std::mt19937 e;
std::uniform_int_distribution<int> u(0, 3);
std::uniform_int_distribution<int> uw(-wp, width + wp);
std::uniform_int_distribution<int> uh(-hp, height + hp);
std::uniform_int_distribution<int> uab(-2, 2);
std::uniform_int_distribution<int> ua(0, 3);

SDL_Surface *img;
SDL_Surface *img1;
SDL_Surface *img2;
SDL_Surface *img3;

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
    // 创建整型随机数分布器，生成指定范围内的随机数
    std::uniform_int_distribution<int> dis_x(-wp, width + wp);
    std::uniform_int_distribution<int> dis_y(-hp, height + hp);
    std::uniform_int_distribution<int> dis_dir(0, 3);
    std::uniform_int_distribution<int> dis_step(-3, 3);

    // 生成敌人位置和路线
    if (enemy_index > -1 && enemy_index < enemy_cnt * 2) {
        // 计算敌人位置
        int x = 0, y = 0;
        switch (dis_dir(gen)) {
        case 0:
            x = -1;
            y = dis_y(gen);
            break;
        case 1:
            x = dis_x(gen);
            y = -1;
        case 2:
            x = width + 1;
            y = dis_y(gen);
            break;
        case 3:
            x = dis_x(gen);
            y = height + 1;
            break;
        }

        // 计算敌人路线
        int dx = dis_step(gen);
        int dy = dis_step(gen);

        // 将敌人位置和路线保存到列表中
        enemies[enemy_index] = std::make_pair(x, y);
        enemies[enemy_index + enemy_cnt] = std::make_pair(dx, dy);
    }
}

void random_xyab(int *ret, int i){

    // 生成随机数种子
    std::random_device rd;
    // 使用新的种子初始化随机数生成器
    e.seed(rd());

    switch(u(e)){
    case 0:
        ret[0] = uh(e);
        ret[1] = -wp;
        break;
    case 1:
        ret[0] = -hp;
        ret[1] = uw(e);
        break;
    case 2:
        ret[0] = uh(e);
        ret[1] = width + wp;
        break;
    case 3:
        ret[0] = height + hp;
        ret[1] = uw(e);
        break;
    }
    fmt::print("{} {}\n", ret[0], ret[1]);
    ret[2] = -ua(e);
    if((ret[0] < height/2 && ret[1] < width/2) || (ret[0] > height/2 && ret[1] > width/2))
        ret[2] = -ret[2];
    ret[3] = uab(e);

    _enemy[i].update_loc(ret[0], ret[1]);
}

void enemy_move_init(int i){
    /*random_xyab(enemy_loc[i], i);
    enemy_loc[i][4] = ((sqrt(width * width + height * height)/(fps * 4))
                        / sqrt(enemy_loc[i][2] * (enemy_loc[i][2] + 1))) + 1;
    if(enemy_loc[i][2] < 0){
        enemy_loc[i][4] = -enemy_loc[i][4];
    }*/
    random_enemy(i, enemies);
}


void enemy_move(){
    int x, y, w, h;
    auto r = enemy.ret_rect();
    w = r->w;
    h = r->h;

    /*
    for(int i = 0; i < enemy_cnt; ++i){
        r = _enemy[i].ret_rect();
        y = r->y + enemy_loc[i][4];
        x = y * enemy_loc[i][2] + enemy_loc[i][3];
        _enemy[i].update_loc(x, y);
        if(y > width + wp + 20 || y < -wp - 20 || x > height + hp + 20 || x < -hp - 20){
            enemy_move_init(i);
        }
    }
    */
    
   for(int i = 0; i < enemy_cnt; ++i){
        r = _enemy[i].ret_rect();
        x = enemies[i + 20].first + r->x;
        y = enemies[i + 20].second + r->y;
        _enemy[i].update_loc(x, y);
        if(y > width + wp + 20 || y < -wp - 20 || x > height + hp + 20 || x < -hp - 20){
            enemy_move_init(i);
        }
    }
}

/*void player_move(int key){
    
}*/


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
    wp = enemy.ret_rect()->w * 2;
    hp = enemy.ret_rect()->h * 2;
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