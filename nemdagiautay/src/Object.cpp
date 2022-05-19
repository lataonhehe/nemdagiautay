#include "Object.h"
#include "include.h"

Object::Object(const char* path, int x, int y)
{
    figurePic = path;
    //Initialize the offsets
    mPosX = x;
    mPosY = y;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    frame=0;
    width_frame=0;
    height_frame=0;
    on_ground= true;

    status= WALK_NONE;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    input_type_.shoot_ = 0;

    jump_sound = Mix_LoadWAV("media/sound/jump.wav");
    throw_sound = Mix_LoadWAV("media/sound/throw.wav");
}

Object::~Object()
{
    Free();
}

SDL_Rect Object::GetRectFrame()
{
    SDL_Rect rect = objTexture.getRect();
    rect.w = rect.w/num_frame;
    return rect;
}

void Object::doObject(Map& map_game)
{
    mVelX = 0;
    mVelY += GRAVITY_SPEED;

    if(input_type_.shoot_ == 1){
        Weapon* pWeapon = new Weapon();
        pWeapon->loadFromFile("media/img/weapon/"+name_weapon+".png");

        if (status == WALK_LEFT)
        {
            pWeapon->set_dir_weapon(Weapon::DIR_LEFT);
            pWeapon->setRect(mPosX - 20, mPosY - pWeapon->getRect().h);
        }
        else
        {
            pWeapon->set_dir_weapon(Weapon::DIR_RIGHT);
            pWeapon->setRect(mPosX + 20, mPosY - pWeapon->getRect().h);
        }
        //pWeapon->set_move_type(BulletObject::SIN_TYPE);

        pWeapon->set_is_moving(true);
        weapon_list.push_back(pWeapon);

        input_type_.shoot_ = 0;

        Mix_PlayChannel(-1, throw_sound, 0);
    }

    if (mVelY >= MAX_FALL_SPEED)
    {
        mVelY = MAX_FALL_SPEED;
    }

    if (input_type_.left_ == 1)
    {
        mVelX -= PLAYER_SPEED;
        status = WALK_LEFT;
    }

    if (input_type_.right_ == 1)
    {
        mVelX += PLAYER_SPEED;
        status = WALK_RIGHT;
    }

    if (input_type_.jump_ == 1)
    {

        if (on_ground == true)
        {
            Mix_PlayChannel(-1, jump_sound, 0);
            mVelY = -PLAYER_HIGHT_VAL;
        }
        on_ground = false;
    }

    CheckToMap(map_game);

}

void Object::handleWeapon(Map& game_map)
{
    for (int i = 0; i < weapon_list.size(); i++)
    {
        Weapon* pWeapon = weapon_list.at(i);
        if (pWeapon != NULL)
        {
            if (pWeapon->moving())
            {
                pWeapon->handleMove(game_map);
                if(pWeapon->moving()) pWeapon->renderTexture(NULL);
            }
            else
            {
                if (pWeapon != NULL)
                {
                    weapon_list.erase(weapon_list.begin() + i);
                    delete pWeapon;
                    pWeapon = NULL;
                }
            }
        }
      }
}

void Object::removeWeapon(const int& idx)
{
    if (weapon_list.size() > 0 && idx < weapon_list.size())
    {
        Weapon* pWeapon = weapon_list.at(idx);
        weapon_list.erase(weapon_list.begin() + idx);

        if (pWeapon)
        {
            delete pWeapon;
            pWeapon = NULL;
        }
    }
}

void Object::render()
{
    updateObject();

    if((input_type_.left_ == 1 ||input_type_.right_ == 1  )){
        frame++;
    }
    else{
        frame = 0;
    }

    if( frame >= num_frame ){
        frame = 0;
    }

    SDL_Rect* currentClip = &gSpriteClips[ frame ];
    objTexture.setRect(mPosX,mPosY);
    objTexture.renderTexture( currentClip );

    name.setRect(mPosX,mPosY+height_frame+20);
    name.loadFromRenderedText(text_font);
    name.renderTexture(NULL);
}

void Object::set_clips()
{
    if(width_frame>0 && height_frame>0){
        for(int i=0;i<num_frame;i++){
            gSpriteClips[ i ].x = width_frame*i;
            gSpriteClips[ i ].y = 0;
            gSpriteClips[ i ].w = width_frame;
            gSpriteClips[ i ].h = height_frame;
		}
    }
}

void Object::updateObject()
{
    std::string path = figurePic;
    if(status == WALK_RIGHT) path+= "right.jpg";
    else if(status == WALK_LEFT) path+= "left.jpg";
    else path+= "right.png";

    if( !LoadImg( path ) )
	{
		std::cout<< "Failed to load walking animation texture!\n" ;
	}
	else
	{
		//Set sprite clips
		set_clips();
	}
}

bool Object::LoadImg(std::string path)
{
    bool ret = objTexture.loadFromFile(path);
    SDL_Rect rect= objTexture.getRect();

    if (ret == true)
    {
        width_frame = rect.w/num_frame;
        height_frame = rect.h;
    }

    return ret;
}

void Object::CheckToMap(Map& map_game)
{
    //Figure to map
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    //Check Horizontal
    //on_ground_ = false;
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;    //SDLCommonFunc::GetMin(height_frame_ TILE_SIZE);

    /*
            x1,y1***x2
            *       *
            *       *
            *       *
            *y2******

    */
    x1 = (mPosX + mVelX) / TILE_SIZE;
    x2 = (mPosX + mVelX + width_frame - 1) / TILE_SIZE;

    y1 = (mPosY) / TILE_SIZE;
    y2 = (mPosY + height_min - 1) / TILE_SIZE;

    // Check x1, x2 with full width of map
    // Check y1, y2 with full heigth of map
    if (x1 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y2 < SCREEN_HEIGHT)
    {
        if (mVelX > 0) // when object is moving by right  ===>
        {
            int val1 = map_game.tileMap[y1][x2];
            int val2 = map_game.tileMap[y2][x2];
            // Check current position of map. It is not blank_tileMap.
            if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
            {
                // Fixed post of object at current post of map.
                // => Cannot moving when press button
                mPosX = x2 * TILE_SIZE;
                mPosX -= width_frame + 1;
                mVelX = 0; // cannot moving
            }
    }
    else if (mVelX < 0) // When moving by left    <====
    {
        int val1 = map_game.tileMap[y1][x1];
        int val2 = map_game.tileMap[y2][x1];

        if ((map_game.tileMap[y1][x1] != BLANK_TILE) || (map_game.tileMap[y2][x1] != BLANK_TILE))
        {
                mPosX = (x1 + 1) * TILE_SIZE;
                mVelX = 0;
        }

    }
    }

      // Check vertical
    int width_min =  width_frame < TILE_SIZE ? width_frame : TILE_SIZE;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

    x1 = (mPosX) / TILE_SIZE;
    x2 = (mPosX + width_min) / TILE_SIZE;

    y1 = (mPosY + mVelY) / TILE_SIZE;
    y2 = (mPosY + mVelY + height_frame -1) / TILE_SIZE;

    if (x1 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y2 < SCREEN_HEIGHT)
    {
        if (mVelY > 0)
        {
            //Similar for vertical
            int val1 = map_game.tileMap[y2][x1];
            int val2 = map_game.tileMap[y2][x2];

            if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
            {
                mPosY = y2 * TILE_SIZE;
                mPosY -= height_frame;

                mVelY = 0;

                on_ground = true;
                if (status == WALK_NONE)
                {
                    //input_type_.right_ = 1;
                    status = WALK_RIGHT;
                }
            }

        }
        else if (mVelY < 0)
        {
            int val1 = map_game.tileMap[y1][x1];
            int val2 = map_game.tileMap[y1][x2];

            if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
            {
                mPosY = (y1 + 1) * TILE_SIZE;

                mVelY = 0;
            }

        }
    }

      //If there is not collision with map tileMap.

    mPosX += mVelX;
    mPosY += mVelY;
    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX + width_frame >= SCREEN_WIDTH)
    {
        mPosX = SCREEN_WIDTH - width_frame - 1;
    }

    //Weapon to map
    for(int w = 0; w<weapon_list.size();w++){
        Weapon* p_weapon = weapon_list.at(w);
        SDL_Rect rec = p_weapon->getRect();

        int x = (rec.x)/TILE_SIZE;
        int y = (rec.y)/TILE_SIZE;
        int x1 = (rec.x+rec.w)/TILE_SIZE;
        int y1 = (rec.y+rec.h)/TILE_SIZE;

        if(map_game.tileMap[y][x] != BLANK_TILE || map_game.tileMap[y1][x1] != BLANK_TILE){
            removeWeapon(w);
        }
    }

}
