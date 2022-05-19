#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Texture.h"
#include "Weapon.h"
#include "commonFunc.h"
#include "Map.h"

//The dot that will move around on the screen
class Object : public Texture{
    public:
        int status;
        Input input_type_;

		//Initializes the variables
		Object(const char* path, int x, int y);
		~Object();
        void updateObject();
		bool LoadImg( std::string path );

		//Moves the dot
		void move();
        void doObject(Map& map_game);
		//Shows the dot on the screen
		void render();
        void set_clips();

        SDL_Rect GetRectFrame();

		void CheckToMap(Map& map_game);

        std::vector<Weapon*> get_weapon_list() const{ return weapon_list; }
        void set_weapon_list(std::vector<Weapon*> w_list){
            weapon_list = w_list;
        }

        void setWeapon(std::string name_wea ){ name_weapon = name_wea; }
        void handleWeapon(Map& game_map);
        void removeWeapon(const int& idx);

        void set_name(std::string name_player){name.SetText(name_player);}
        std::string get_name(){ return name.GetText(); }

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        SDL_Rect gSpriteClips[ num_frame ];
		int frame;

		int width_frame;
		int height_frame;

		bool on_ground;

        std::string figurePic;
        Texture objTexture;
        Texture name;
        TTF_Font* text_font = TTF_OpenFont("media/font//fontText.ttf", 18);

		SDL_Rect frame_clip_[num_frame];
		std::vector<Weapon*> weapon_list;
		std::string name_weapon = "0";

		Mix_Chunk* jump_sound;
		Mix_Chunk* throw_sound;

};



#endif // OBJECT_H_INCLUDED
