#pragma once

#include "include.h"
#include "commonFunc.h"

class Texture
{
	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

        void setRect(const int& x, const int& y, const int& w, const int &h) {rect_.x = x, rect_.y = y; rect_.w= w; rect_.h= h;};
        void setRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
        SDL_Rect getRect() const {return rect_;}
        SDL_Texture* getObject() {return mTexture;}
		//Loads image at specified path
		bool loadFromFile( std::string path );
		bool loadFromRenderedText( TTF_Font* text_font );

        //Renders texture at given point
        void renderTexture( const SDL_Rect* clip );
		//Deallocates texture
		void Free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		void SetText(const std::string& text) {str_val = text;}
        std::string GetText() const {return str_val;}

	protected:
		//The actual hardware texture
		SDL_Texture* mTexture;

		SDL_Color text_color = {255, 255, 255};

		std::string str_val = "";

		//Image dimensions
		SDL_Rect rect_;
};



//#endif // TEXTURE_H_INCLUDED

