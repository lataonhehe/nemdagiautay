#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "commonFunc.h"
#include "include.h"
#include "Texture.h"
#include "Timer.h"

bool click_button(Texture button);
//Menu
void init_menu();
void render_menu();
void show_menu();
void close_menu();
void show_options();

Texture play_button;
Texture option_button;
Texture sound_button;
Texture music_button;

Texture back_ground;

Mix_Chunk* click_sound;
Mix_Music* menu_sound;

void init_menu()
{
    back_ground.loadFromFile("media/img/menu.png");
    back_ground.setRect(0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    play_button.loadFromFile("media/img/button/play.png");
    play_button.setRect(520,390);
    option_button.loadFromFile("media/img/button/option.png");
    option_button.setRect(520,490);

    click_sound = Mix_LoadWAV("media/sound/click.wav");
    menu_sound = Mix_LoadMUS("media/sound/menu.mp3");
    if(!Mix_PlayingMusic()) Mix_PlayMusic(menu_sound, -1);

}
void render_menu()
{
    SDL_RenderClear(Game::renderer);

    back_ground.renderTexture(NULL);

    SDL_PollEvent(&Game::event);
    if(Game::event.type == SDL_QUIT) Game::status_ = QUIT;
    if(Game::event.type == SDL_MOUSEBUTTONDOWN){
        Mix_PlayChannel(-1,click_sound,0);
    }
    int xm,ym;
    SDL_GetMouseState(&xm,&ym);

    if(Collision::CheckFocus(xm,ym,play_button.getRect()) == true)
    {
        play_button.loadFromFile("media/img/button/play_pressed.png");
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Game::status_ = START;
            Mix_FreeMusic(menu_sound);
            Mix_FreeChunk(click_sound);
        }
    }
    else play_button.loadFromFile("media/img/button/play.png");

    if(Collision::CheckFocus(xm,ym,option_button.getRect()) == true)
    {
        option_button.loadFromFile("media/img/button/option_pressed.png");
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Game::status_ = OPTIONS;
        }
    }
    else option_button.loadFromFile("media/img/button/option.png");

    play_button.renderTexture(NULL);
    option_button.renderTexture(NULL);

    SDL_RenderPresent(Game::renderer);

    Game::fps.keep_fps();
}

void close_menu()
{
    //fps.stop();
    back_ground.Free();
    play_button.Free();
    option_button.Free();
    music_button.Free();
    sound_button.Free();
}

void show_menu()
{
    init_menu();
    while(Game::status_ == MENU){
         render_menu();
    }
    close_menu();
}
//options
int choose_weapon(const int& x, const int& y ,int mPosX, int mPosY)
{
    SDL_Rect rect_;
    rect_.w = 64;
    rect_.h = 64;
    for(int i=0;i<4;i++){
        rect_.y = mPosY+rect_.h*i;
        for(int j=0;j<4;j++){
            rect_.x = mPosX+rect_.w*j;
            if(Collision::CheckFocus(x, y, rect_)){
                return i*4+j;
            }
        }
    }
    return 0;
}

void show_options()
{
    Texture weapon1_demo;
    Texture weapon2_demo;

    weapon1_demo.setRect(285,480);
    weapon2_demo.setRect(965,480);

    SDL_Rect table1 = {175,155,264,264};
    SDL_Rect table2 = {855,155,264,264};

    Texture menu_button;
    menu_button.setRect(SCREEN_WIDTH/2-110,400,180,60);

    back_ground.loadFromFile("media/img/options.png");
    back_ground.setRect(0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    while(Game::status_ == OPTIONS){
        SDL_RenderClear(Game::renderer);
        //check mouse
        SDL_PollEvent(&Game::event);
        if(Game::event.type == SDL_QUIT) Game::status_ = QUIT;
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            Mix_PlayChannel(-1,click_sound,0);
        }
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);

        if(Collision::CheckFocus(xm,ym,menu_button.getRect()))
        {
            menu_button.loadFromFile("media/img/button/menu_pressed.png");
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                    Game::status_ = MENU;
                    Mix_PlayChannel(-1,click_sound,0);
            }
        }
        else menu_button.loadFromFile("media/img/button/menu.png");

        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            if(Collision::CheckFocus(xm, ym , table1))
                Game::weapon1 = std::to_string(choose_weapon(xm, ym, table1.x, table1.y));
            if(Collision::CheckFocus(xm, ym , table2))
                Game::weapon2 = std::to_string(choose_weapon(xm, ym, table2.x, table2.y));
        }

        weapon1_demo.loadFromFile("media/img/weapon/"+Game::weapon1+".png");
        weapon2_demo.loadFromFile("media/img/weapon/"+Game::weapon2+".png");

        //render
        back_ground.renderTexture(NULL);
        menu_button.renderTexture(NULL);
        weapon1_demo.renderTexture(NULL);
        weapon2_demo.renderTexture(NULL);

        SDL_RenderPresent(Game::renderer);

        Game::fps.keep_fps();
    }

    weapon1_demo.Free();
    weapon2_demo.Free();
    back_ground.Free();
    menu_button.Free();
}



#endif // MENU_H_INCLUDED
