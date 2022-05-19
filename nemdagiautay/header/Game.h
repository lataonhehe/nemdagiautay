#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include.h"
#include "Object.h"
#include "Map.h"
#include "Object.h"
#include "commonFunc.h"
#include "Geometric.h"
#include "Power.h"

class Game
{
public:

    Game();
    ~Game();

    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void start_game();
    void render();
    void clean();
    void close();
    void play_game();
    void game_over();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static int status_ ;
    static bool gamequit;
    static Timer fps;
    static std::string weapon1;
    static std::string weapon2;

private:
    std::string player_win;
    SDL_Window* window;
    Mix_Music* theme_music;

    Object* player1;
    Object* player2;
    Health player1_health;
    Health player2_health;

};


#endif // GAME_H_INCLUDED
