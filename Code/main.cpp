#include "helpers.hpp"

int main(int argc, char* argv[]){


    unsigned int frameStart;
    int frameTime;

    init();
    if(main_menu() < 0) return -1;
    if(quit) return 0;
    game = new Game();
    if(Game::server){
        Game::window_h = Game::wall_thickness + Game::menu + Game::block_h * Game::rows + (Game::rows - 1) * Game::wall_thickness;
        Game::window_w = 2 * Game::wall_thickness + Game::block_w * Game::cols + (Game::cols - 1) * Game::wall_thickness;
        game->init("Server", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    }
    else if(Game::client){
        Game::window_h = Game::wall_thickness + Game::menu + Game::block_h * Game::rows + (Game::rows - 1) * Game::wall_thickness;
        Game::window_w = 2 * Game::wall_thickness + Game::block_w * Game::cols + (Game::cols - 1) * Game::wall_thickness;
        game->init("Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    }
    else game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    if(Game::task == 1) Mix_PlayMusic( Game::gMusic, -1 );
    int ct = 0;
    while(game->running()){
        frameStart = SDL_GetTicks();
        if(Game::server){
            server_work();
        }
        else if(Game::client){
            client_work();
        }
        // if(!Game::isRunning) break;
        game->handleEvents();
        if(Game::task == 1){
            game->update();
        }
        else if(Game::task == 2 and ct < Game::FPS * 3){
            ct++;
        }
        else{
            game->update();
        }
        game->handle_collisions();
        game->render();

        // cout << Entity::in_sight(game->entities->players->at(0),game->entities->monsters->at(1) ) << endl;
        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

        key_testing();


    }
    Mix_HaltMusic();
    game->clean();
    if(Game::client == 1 and Game::quit == 1){
        string message = "quit";
        for(int i=0;i<20;i++)
        int sendRes = send(sock, message.c_str(), message.size()+1, 0);
    }
    else if(Game::server == 1 and Game::quit == 1){
        string message = "quit";
        cout<<"ok"<<endl;
        for(int i=0;i<20;i++)
        int sendRes = send(clientSocket, message.c_str(), message.size()+1, 0);
    }
    else if(Game::quit == 1 or Game::win == 0){
        Mix_PlayChannel( -1, Game::game_lose, 0 );
    }
    else{
        Mix_PlayChannel( -1, Game::game_win, 0 );
    }
    // main_menu();
    if(Game::task == 1){
        Mix_PlayMusic( Game::ending, -1 );
        winning_message();
    }
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}