#include "Game.hpp"

Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return 1;
    }
    int port = 54000;
    string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), & hint.sin_addr);
    int connectRes = connect(sock, (struct sockaddr * ) & hint, sizeof(hint));
    if(connectRes == -1){
        return 1;
    }
    char buf[4096];
    string command;
    command = "start";
    int sendRes = send(sock, command.c_str(), command.size()+1, 0);
    if(sendRes == -1){
        cout<<"Could not send through server"<<endl;
    }
    memset(buf, 0, 4096);
    int bytesRecv = recv(sock, buf, 4096, 0);
    Game::seed = stoi(string(buf, bytesRecv));


    game = new Game();
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    
    game->player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 60);
    game->player2 = new Remote(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, 0);
    
    Game::entities->Add(game->player1);
    Game::entities->Add(game->player2);
    game->monster->set_dest(game->player1);


    while(game->running()){
        if (Game::response < 0) Game::response = 0;
        command = to_string(Game::send);
        int sendRes = send(sock, command.c_str(), command.size()+1, 0);
        if(sendRes == -1){
            cout<<"Could not send through server"<<endl;
        }
        memset(buf, 0, 4096);
        int bytesRecv = recv(sock, buf, 4096, 0);
        string response = string(buf, bytesRecv);
        Game::response = stoi(response);
        cout<<response<<endl;
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

    }
    close(sock);
    game->clean();
}