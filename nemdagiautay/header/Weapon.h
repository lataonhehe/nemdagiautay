#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "commonFunc.h"
#include "Texture.h"
#include "Timer.h"
#include "Map.h"

class Weapon : public Texture
{
public:
    Weapon();
    ~Weapon();

    enum weaponDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UP_LEFT = 23,
        DIR_UP_RIGHT = 24,
    };

    enum weaponType
    {
        NONE,
        ROCK,
        TURTLE,
    };

    enum MoveType
    {
        LINE_TYPE = 10,
        SIN_TYPE = 11
    };

    void set_x_val(const int& x){ xVal = x; }
    void set_y_val(const int& y){ yVal = y; }
    int get_x_val() const{ return xVal; }
    int get_y_val() const{ return yVal; }

    void set_is_moving(const bool& isMov){ isMoving = isMov; }
    bool moving(){ return isMoving; }
    void set_dir_weapon(const int& dir_type){ weapon_dir = dir_type; }

    void handleMove(Map& game_map);

    Timer time;

private:
    int xVal;
    int yVal;

    bool isMoving;
    int weapon_dir;
    int move_type;

};

#endif // WEAPON_H_INCLUDED
