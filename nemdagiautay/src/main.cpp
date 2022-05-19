#include "include.h"
#include "commonFunc.h"
#include "Game.h"
#include "Timer.h"
#include "Menu.h"
Game *game = nullptr;

int main(int argv, char* args[])
{
    game = new Game();
    game->init("Ném đá giấu tay", SCREEN_WIDTH, SCREEN_HEIGHT);
    while(Game::status_ != QUIT){
        SDL_PollEvent(&Game::event);
        if(Game::event.type == SDL_QUIT) break;
        switch(Game::status_)
        {
            case MENU: show_menu(); break;

            case OPTIONS: show_options(); break;

            case START: game->play_game(); break;

            case GAMEOVER: game->game_over(); break;

            case QUIT: game->close(); break;

        }
        Game::fps.keep_fps();
    }
    game->close();

    return 0;
}
