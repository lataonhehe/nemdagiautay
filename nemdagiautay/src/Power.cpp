#include "Power.h"
#include "include.h"
Health::Health(void)
{}

Health::~Health(void)
{}

void Health::Init(int start_, std::string name)
{
    img.loadFromFile("media/img/health.png");
    lives = 5;
    alive = true;
    start = start_;
    text_font = TTF_OpenFont("media/font//fontText.ttf", 20);
    name_player.SetText(name);
    name_player.loadFromRenderedText(text_font);
    if(direct != 1) name_player.setRect(start-name_player.getRect().w+25, 12);
    else name_player.setRect(start, 12);

    hurt_sound = Mix_LoadWAV("media/sound/hurt.wav");

}

void Health::Show()
{
    for(int i=0; i<lives;i++){
        img.setRect(start+(i*img.getRect().w)*direct, 8);
        img.renderTexture(NULL);
    }
    name_player.renderTexture(NULL);
}

void Health::Decrease()
{
    Mix_PlayChannel(-1,hurt_sound,0);
    lives--;
    if(lives <= 0) alive = false;
}
