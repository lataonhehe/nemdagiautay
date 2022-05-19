#include "commonFunc.h"
#include "Weapon.h"

Weapon::Weapon()
{
    xVal = 0;
    yVal = 0;

    //isMoving = false;

    move_type = SIN_TYPE;
    time.start();
}

Weapon::~Weapon()
{

}

void Weapon::handleMove(Map& game_map)
{
    double time_in_air = double(time.get_ticks())/500;
    if (weapon_dir == DIR_RIGHT)
    {
        rect_.x += speed_weapon*time_in_air*cos(angle);
    }
    else if (weapon_dir == DIR_LEFT)
    {
        rect_.x -= speed_weapon*time_in_air*cos(angle);
    }
    if(time_in_air <= ((speed_weapon*sin(angle))/GRAVITY_SPEED))
        rect_.y -= (speed_weapon*sin(angle)*time_in_air - GRAVITY_SPEED*time_in_air*time_in_air/2);
    else rect_.y += (GRAVITY_SPEED*time_in_air*time_in_air/2);

    //check
    int x = (rect_.x + rect_.w)/TILE_SIZE;
    if(weapon_dir == DIR_LEFT) x = (rect_.x - rect_.w)/TILE_SIZE;

    int y = (rect_.y)/TILE_SIZE;

    if(game_map.tileMap[y][x] != BLANK_TILE){
            isMoving = false;
    }
}
