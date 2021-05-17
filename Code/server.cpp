#include "sockets.hpp"

int main(int argc, char* argv[]){
    int res = create_server();
    if(res<0) return -1;
    init();

    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    if(Game::task == 1){
        game->player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0, 1, 6, 100);
        Game::entities->Add(game->player1);
        game->player2 = new Remote(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0, 1, 6, 100);
        Game::entities->Add(game->player2);
        game->monster->set_mode(0, game->player1);
        game->snitch->scary_target = game->player1;

    }

    Mix_PlayMusic( Game::gMusic, -1 );


    // Array of pthreads
    
    
    while(game->running()){
        if(receive == true){
            data[0].part = 0;
            pthread_create( & threads[0], NULL, temporal, (void * ) & data[0]);
            receive = false;
        }
        // if(sending == true){
        //     data[1].part = 1;
        //     pthread_create( & threads[1], NULL, temporal, (void * ) & data[1]);
        //     sending = false;
        // }
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

    }

    for(int i = 0; i < 1;i++){
        pthread_join(threads[i], NULL); // Wait for each thread to finish
    }
    close(clientSocket);
    game->clean();
}


void * temporal(void * arg) {
    // Argument to thread
    struct thread_data * my_data;
    my_data = (struct thread_data * ) arg;
    int part = my_data->part;
    string delim = ",";
    if(part == 0){
        if (Game::response < 0) Game::response = 0;
        int sent = Game::send;
        string pos = to_string(game->player1->xpos)+","+to_string(game->player1->ypos)+","+to_string(game->player1->xv)+","+to_string(game->player1->yv);
        int sendRes = send(clientSocket, pos.c_str(), pos.size()+1, 0);
        if(sendRes == -1){
            cout<<"Could not send through server"<<endl;
        }
        cout<<sent<<endl;
        sending = true;
        prevSend = sent;
        memset(buf, 0, 4096);
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if(bytesRecv == -1){
            cout<<"Connection issue"<<endl;
            receive = true;
            return 0;
        }
        if(bytesRecv == 0){
            cout<<"Client disconnected"<<endl;
            receive = true;
            return 0;
        }
        string command = string(buf, 0, bytesRecv);
        vector<string> process;
        tokenize(command, delim, process);
        game->player2->xpos = stoi(process[0]);
        game->player2->ypos = stoi(process[1]);
        game->player2->xv = stoi(process[2]);
        game->player2->yv = stoi(process[3]);
        // Game::response = stoi(command);
        receive = true;
    }
    else{
        
        
    }
    return (void *) 0;
}