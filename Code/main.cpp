#include "helpers.hpp"

int main(int argc, char* argv[]){


    unsigned int frameStart;
    int frameTime;

    init();
    if(main_menu() < 0) return -1;
    if(quit) return 0;
    srand(time(0));
    Game::seed = rand()%100000;
    game = new Game();
    if(Game::server)
        game->init("Server", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    else if(Game::client){
        game->init("Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    }
    else game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    if(Game::task == 1){

        // game->player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0, 1, 6, 100);
        // Game::entities->Add(game->player1);
        if(Game::client){
            game->player2 = new Remote(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0, 2, 6, 100);
            Game::entities->Add(game->player2);
        }
        else if(Game::server){
            game->player2 = new Remote(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, Game::cols-1, 2, 6, 100);
            Game::entities->Add(game->player2);
        }
        // game->monster->set_mode(0, game->player1);
        // game->monster->scary_target = game->player1;

        // game->snitch->scary_target = game->player1;

    }
    if(Game::task == 1) Mix_PlayMusic( Game::gMusic, -1 );
    int ct = 0;
    while(game->running()){
        frameStart = SDL_GetTicks();
        // cout<<Game::send<<endl;
        cout<<Game::response<<endl;
        string delim = ",";
        if(Game::server){
            if (Game::response < 0) Game::response = 0;
            int sent = Game::send;
            string pos = to_string(game->player1->xpos)+","+to_string(game->player1->ypos)+","+to_string(game->player1->xv)+","+to_string(game->player1->yv);
            // string pos = to_string(sent);
            // if(prevSend != sent){
                int sendRes = send(clientSocket, pos.c_str(), pos.size()+1, 0);
                if(sendRes == -1){
                    cout<<"Could not send through server"<<endl;
                }
            // }
            // cout<<sent<<endl;
            // sending = true;
            prevSend = sent;
            memset(buf, 0, 4096);
            int bytesRecv = recv(clientSocket, buf, 4096, 0);
            if(bytesRecv == -1){
                cout<<"Connection issue"<<endl;
                // receive = true;
                // return 0;
            }
            if(bytesRecv == 0){
                cout<<"Client disconnected"<<endl;
                // receive = true;
                // return 0;
            }
            string command = string(buf, 0, bytesRecv);
            vector<string> process;
            tokenize(command, delim, process);
            game->player2->xpos = stoi(process[0]);
            game->player2->ypos = stoi(process[1]);
            game->player2->xv = stoi(process[2]);
            game->player2->yv = stoi(process[3]);
            // cout<<command<<endl;
            // if(command.size()>0)
                // Game::response = stoi(command);
        }
        else if(Game::client){
            if (Game::response < 0) Game::response = 0;
            string command = to_string(Game::send);
            string pos = to_string(game->player1->xpos)+","+to_string(game->player1->ypos)+","+to_string(game->player1->xv)+","+to_string(game->player1->yv);
            // string pos = command;
            int sent = Game::send;
            // if(prevSend != sent){
                int sendRes = send(sock, pos.c_str(), pos.size()+1, 0);
                if(sendRes == -1){
                    cout<<"Could not send through server"<<endl;
                }
            // }
            
            // cout<<sendRes<<endl;
            prevSend = stoi(command);
            memset(buf, 0, 4096);
            int bytesRecv = recv(sock, buf, 4096, 0);
            string response = string(buf, bytesRecv);
            cout<<response<<endl;
            vector<string> process;
            tokenize(response, delim, process);
            game->player2->xpos = stoi(process[0]);
            game->player2->ypos = stoi(process[1]);
            game->player2->xv = stoi(process[2]);
            game->player2->yv = stoi(process[3]);
            // if(response.size()>0)
                // Game::response = stoi(response);
            // receive = true;
        }
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


        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

        key_testing();


    }
    game->clean();
}