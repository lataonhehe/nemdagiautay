#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
int Game::status_ = QUIT;
bool Game::gamequit = false;
Timer Game::fps;
std::string Game::weapon1 = "0";
std::string Game::weapon2 = "0";

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        status_ = MENU;
    }

    if (TTF_Init() == -1){
        status_ = QUIT;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
		status_ = QUIT;
	}

}

void Game::start_game()
{
    player_win = "";
    theme_music = Mix_LoadMUS("media/sound/theme.mp3");
    Mix_PlayMusic(theme_music,-1);
    player1 = new Object("media/img/player/", 4*TILE_SIZE, 5*TILE_SIZE);
    player1->set_name("player 1");
    player1->LoadImg("media/img/player/right.png");
    player1->setWeapon(weapon1);
    player1_health.Init(2, player1->get_name());

    player2 = new Object("media/img/player/", 15*TILE_SIZE, 5*TILE_SIZE);
    player2->set_name("player 2");
    player2->setWeapon(weapon2);
    player2_health.set_direct(-1);
    player2_health.Init(SCREEN_WIDTH-25 , player2->get_name());


}

void Game::update()
{
    player1->updateObject();
    player2->updateObject();
}

void Game::render()
{
    SDL_RenderClear(renderer);

    //Backsground
    Texture backgr;
    backgr.loadFromFile("media/img/backGround.jpg");
    backgr.setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    backgr.renderTexture(NULL);

    //Health
    GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 40);
    ColorData color_data(36, 36, 36);
    Gemometric::RenderRectange(rectange_size, color_data);

    GeometricFormat outlie_size(1, 1, SCREEN_WIDTH - 1, 38);
    ColorData color_data1(0XFF,0XFF,0XFF);
    Gemometric::RenderOutline(outlie_size, color_data1);


    //Load map
    Map game_map;
    game_map.loadMap("media/map/map.txt");
    game_map.drawMap();


    //Figure move
    player1->doObject(game_map);
    player2->doObject(game_map);

    //Throw weapon
    player1->handleWeapon(game_map);
    player2->handleWeapon(game_map);

    //Check weapon vs figure
    std::vector<Weapon*> weapon_list1 = player1->get_weapon_list();
    std::vector<Weapon*> weapon_list2 = player2->get_weapon_list();
    for(int w=0; w<weapon_list1.size(); w++){
        Weapon* p_weapon = weapon_list1.at(w);
        if(p_weapon){
            bool check = Collision::checkCollision(p_weapon->getRect(), player1->GetRectFrame());
            if( check ){
                player1->removeWeapon(w);
                player1_health.Decrease();
            }
            bool check1 = Collision::checkCollision(p_weapon->getRect(), player2->GetRectFrame());
            if( check1 ){
                player1->removeWeapon(w);
                player2_health.Decrease();
            }
        }
    }
    for(int i=0;i<weapon_list2.size();i++){
        Weapon* p_weapon = weapon_list2.at(i);
        if(p_weapon){
            bool check = Collision::checkCollision(p_weapon->getRect(), player1->GetRectFrame());
            if( check ){
                player2->removeWeapon(i);
                player1_health.Decrease();
            }
            bool check1 = Collision::checkCollision(p_weapon->getRect(), player2->GetRectFrame());
            if( check1 ){
                player2->removeWeapon(i);
                player2_health.Decrease();
            }
        }
    }
//Render
    player1_health.Show();
    player2_health.Show();

    player1->render();
    player2->render();

    SDL_RenderPresent(renderer);

    if (player1_health.isAlive() == false || player2_health.isAlive() == false)
    {
        status_ = GAMEOVER;
        if(player1_health.isAlive()) player_win = player1->get_name();
        else player_win = player2->get_name();
    }

    Game::fps.keep_fps();

}

void Game::clean()
{
    //Game::fps.stop();
    Mix_FreeMusic(theme_music);
    delete player1;
    delete player2;
    player1_health.Free();
    player2_health.Free();
}

void Game::close()
{
    theme_music = NULL;
    renderer = NULL;
    window = NULL;
    Mix_FreeMusic(theme_music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::game_over()
{
    //init
    Mix_Music* victory_sound = Mix_LoadMUS("media/sound/victory.mp3");
    Mix_PlayMusic(victory_sound, -1);
    Mix_Chunk* click_sound = Mix_LoadWAV("media/sound/click.wav");

    Texture new_game_button;
    new_game_button.setRect(SCREEN_WIDTH/2-130,300,180,60);
    Texture menu_button;
    menu_button.setRect(SCREEN_WIDTH/2-130,400,180,60);

    TTF_Font* font_text = TTF_OpenFont("media/font/MatchupPro.ttf", 80);
    Texture victory_text;

    while(Game::status_ == GAMEOVER){
        //checkbutton
        SDL_PollEvent(&event);

        if( event.type == SDL_QUIT ){
            status_ = QUIT;
        }
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);
        if(Collision::CheckFocus(xm,ym,menu_button.getRect()) == true)
        {
            menu_button.loadFromFile("media/img/button/menu_pressed.png");
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                    Game::status_ = MENU;
                    Mix_PlayChannel(-1,click_sound,0);
            }
        }
        else menu_button.loadFromFile("media/img/button/menu.png");

        if(Collision::CheckFocus(xm,ym,new_game_button.getRect()) == true)
        {
            new_game_button.loadFromFile("media/img/button/new_game_pressed.png");
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                Game::status_ = START;
                Mix_PlayChannel(-1,click_sound,0);
            }
        }
        else new_game_button.loadFromFile("media/img/button/new_game.png");

        //congratulation
        victory_text.SetText(player_win+" win!");
        victory_text.loadFromRenderedText(font_text);
        victory_text.setRect(SCREEN_WIDTH/2 - victory_text.getRect().w/2, 200);
        victory_text.renderTexture(NULL);
        //render
        new_game_button.renderTexture(NULL);
        menu_button.renderTexture(NULL);

        SDL_RenderPresent(Game::renderer);

        Game::fps.keep_fps();
    }

    TTF_CloseFont(font_text);
    victory_text.Free();
    new_game_button.Free();
    menu_button.Free();
    Mix_FreeChunk(click_sound);
    Mix_FreeMusic(victory_sound);
    //clean();
}

void Game::play_game()
{
    start_game();
    while(status_ == START){
        handleEvents();
        update();
        render();
    }
    clean();
}
void Game::handleEvents()
{

    const Uint8* state = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&event);

    if( event.type == SDL_QUIT ){
        status_ = QUIT;
        return;
    }

    if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
        //player1

        if(state[SDL_SCANCODE_D]){
            player1->input_type_.right_ = 1;
            player1->input_type_.left_ = 0;
        }
        else player1->input_type_.right_ = 0;

        if(state[SDL_SCANCODE_A]){
            player1->input_type_.left_ = 1;
            player1->input_type_.right_ = 0;
        }
        else player1->input_type_.left_ = 0;

        if(state[SDL_SCANCODE_W])
            player1->input_type_.jump_= 1;
        else player1->input_type_.jump_= 0;

        if(state[SDL_SCANCODE_T])
            player1->input_type_.shoot_ = 1;
        else player1->input_type_.shoot_ = 0;

        //player2
        if(state[SDL_SCANCODE_RIGHT]){
            player2->input_type_.right_ = 1;
            player2->input_type_.left_ = 0;
        }
        else player2->input_type_.right_ = 0;

        if(state[SDL_SCANCODE_LEFT]){
            player2->input_type_.left_ = 1;
            player2->input_type_.right_ = 0;
        }
        else player2->input_type_.left_ = 0;

        if(state[SDL_SCANCODE_UP])
            player2->input_type_.jump_= 1;
        else player2->input_type_.jump_= 0;

        if(state[SDL_SCANCODE_M])
            player2->input_type_.shoot_ = 1;
        else player2->input_type_.shoot_ = 0;
    }
}
