#include "Game.hpp"

Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;

    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
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