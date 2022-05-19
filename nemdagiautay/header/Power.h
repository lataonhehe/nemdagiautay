#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED


#include "commonFunc.h"
#include "Texture.h"

class Health : public Texture
{
public:

    Health(void);
    ~Health(void);

    void SetLives(const int& num) {lives = num;}
    void AddPos(const int& xPos);
    void Show();
    void Init(int start_, std::string name);
    bool isAlive(){return alive;}
    void set_direct(int dir_){ direct = dir_; }
    void InCrease();
    void Decrease();

private:
    int lives;
    int start;
    bool alive = true;
    int direct = 1;
    Texture img;
    Texture name_player;
    TTF_Font* text_font = NULL;
    Mix_Chunk* hurt_sound;

};

#endif // POWER_H_INCLUDED
