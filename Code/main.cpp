#include "Game.hpp"
#include "Texture.hpp"
Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        Game::isRunning = true;
        if(TTF_Init()==-1) {
            Game::isRunning = false;
        }
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ){
            Game::isRunning = false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            Game::isRunning = false;
        }
    }
    else{
        Game::isRunning = false;
    }
    Game::font = TTF_OpenFont("../Fonts/arial.ttf", 100);
    SDL_Window * window = SDL_CreateWindow("Window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    while(true){
        SDL_RenderClear(renderer);
        SDL_Event event;
        SDL_PollEvent(& event);
        if(event.type == SDL_QUIT){
            break;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState( &x, &y );
                // cout<<x<<" "<<y<<endl;
                break;
            }
        }

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, "Game", SDL_Color{255, 0, 0, 255});
        SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

        SDL_Rect Message_rect;
        Message_rect.w = 150;
        Message_rect.h = 50;
        Message_rect.y = 10;
        Message_rect.x = 100;
        SDL_RenderCopy(renderer, Message, NULL, & Message_rect);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    game->player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0, 1, 6, 100);
    
    // game->player2 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 60);
    Game::entities->Add(game->player1);
    // Game::entities->Add(game->player2);

    game->monster->set_mode_id(0);
    game->monster->set_dest(game->player1);



    Mix_PlayMusic( Game::gMusic, -1 );
    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

    }
    game->clean();
}