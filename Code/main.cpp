#include "Game.hpp"

Game * game = nullptr;

int main(int argc, char* argv[]){

    const int FPS = 180;
    const int frameDelay = 1000 / FPS;
    const int window_h = block_h * rows + (rows - 1) * wall_thickness;
    const int window_w = block_w * cols + (cols - 1) * wall_thickness;
    unsigned int frameStart;
    int frameTime;

    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, false);
    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }
    game->clean();
}