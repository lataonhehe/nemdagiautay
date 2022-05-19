#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include "include.h"

#define TILE_SIZE 64
#define BLANK_TILE 0

#define num_frame 12

#define GRAVITY_SPEED 3
#define MAX_FALL_SPEED 12

#define PLAYER_SPEED 10
#define PLAYER_HIGHT_VAL 30;

#define PI 3.14159265

//Screen
const int FPS = 20;
const int frameDelay = 1000/FPS;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int maxX = 10;
const int maxY = 20;
const int maxTiles = 3;

const int ground = TILE_SIZE*7;

const int RENDER_DRAW_COLOR = 0XFF;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


const double speed_weapon = 10;
const double angle = 60*PI/180.0;


enum game_status
{
    MENU = 10,
    START = 11,
    OPTIONS = 12,
    PAUSE = 13,
    GAMEOVER = 14,
    QUIT = 15,

};

enum walkType
{
    WALK_NONE = 0,
    WALK_RIGHT = 1,
    WALK_LEFT = 2,
};


struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int shoot_;
};

struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height) { left_ = left; top_ = top; width_ = width; height_ = height; }
    int left_;
    int top_;
    int width_;
    int height_;
};

struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b) { red_ = r, green_ = g, blue_ = b; }
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

namespace Collision
{
    bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    bool CheckFocus(const int& x, const int& y, const SDL_Rect& rect);
}


#endif // COMMONFUNC_H_INCLUDED
