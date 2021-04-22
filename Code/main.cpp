#include "Game.hpp"

Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;

    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    game->player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0);
    game->player2 = new Remote(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 60);
    Game::entities->Add(game->player1);
    Game::entities->Add(game->player2);

    game->monster->set_dest(game->player1);

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