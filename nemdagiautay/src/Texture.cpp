#include "Texture.h"
#include "Game.h"

Texture::Texture()
{
    //Initialize
    //SDL_DestroyTexture( mTexture );
	mTexture = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

Texture::~Texture()
{
    //Deallocate
    Free();
}

bool Texture::loadFromFile( std::string path )
{
    Free();

    SDL_Texture* newTexture= NULL;
    SDL_Surface* loadedSurface= IMG_Load(path.c_str());
    if( loadedSurface == NULL){
        std::cout<<"Unable to load image "<<path.c_str()<<"! SDL_Image Error: "<<'\n';
        IMG_GetError();
    }
    else{
        //Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format,0XFF, 0XFF, 0XFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Game::renderer, loadedSurface );
        if( newTexture == NULL ){
            std::cout<<"Unable to create texture from "<<path.c_str()<<"! SDL Error: "<<'\n';
            IMG_GetError();
        }
        else{
            //Get image dimensions
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        //Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
    }
    //Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromRenderedText(TTF_Font* text_font )
{
    //Get rid of preexisting texture
    Free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( text_font, str_val.c_str(), text_color);
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( Game::renderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            rect_.w = textSurface->w;
            rect_.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}


void Texture::Free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		rect_.w = 0;
        rect_.h = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::renderTexture( const SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h};

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( Game::renderer, mTexture, clip, &renderQuad );
}

