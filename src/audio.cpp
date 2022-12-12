#include"audio.hpp"
#include "libheader.hpp"

Mix_Music *music;
Mix_Music *over;

int audio_init(){
    int s = Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    int s1 = Mix_OpenAudio(22050, AUDIO_U8, 1, 1024);
    if(s1 == -1){
        fmt::print("error Openaudio\n");
    }
    music = Mix_LoadMUS("./art/run.ogg");
    if(music == nullptr){
        fmt::print("{}\n", s);
        fmt::print("error music\n");
    }
    over = Mix_LoadMUS("./art/gameover.wav");
    if(over == nullptr){
        fmt::print("error music over\n");
    }
    audio_run();
    return 1;
}

int audio_over(){
    Mix_PlayMusic(over, 0);
    return 1;
}

int audio_run(){
    Mix_PlayMusic(music, 0);
    return 1;
}

bool audio_check(){
    if(Mix_PlayingMusic()){
        return true;
    }
    audio_run();
    return false;
}

int free_audio(){
    Mix_FreeMusic(music);
    Mix_FreeMusic(over);
    Mix_Quit();
    return 1;
}