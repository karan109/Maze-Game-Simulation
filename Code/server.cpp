#include "Game.hpp"

Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;

    game = new Game();


    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        cout<<"Can't create socket"<<endl;
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", & hint.sin_addr); // 127.0.0.1
    if(::bind(listening, (struct sockaddr *) & hint, sizeof(hint)) == -1){
        cout<<"Can't bind to IP port"<<endl;
        return -2;
    }
    if(listen(listening, SOMAXCONN) == -1){
        cout<<"Can't listen"<<endl;
        return -3;
    }
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (struct sockaddr *) & client, & clientSize);

    if(clientSocket == -1){
        cout<<"Problem with client connecting!"<<endl;
        return -4;
    }

    close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((struct sockaddr *) & client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if(result){
        cout<<host<<" connected on "<<svc<<endl;
    }
    else{
        inet_ntop(AF_INET, & client.sin_addr, host, NI_MAXHOST);
        cout<<host<<" connected on "<<ntohs(client.sin_port)<<endl;
    }

    char buf[4096];

    while(true){
        memset(buf, 0, 4096);
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if(bytesRecv == -1){
            cout<<"Connection issue"<<endl;
            break;
        }
        if(bytesRecv == 0){
            cout<<"Client disconnected"<<endl;
            break;
        }
        string command_rec = string(buf, 0, bytesRecv);
        // send(clientSocket, buf, bytesRecv + 1, 0);
        if(command_rec == "start"){
            srand(time(0));
            Game::seed = rand()%100000;
            string command_send = to_string(Game::seed);
            int sendRes = send(clientSocket, command_send.c_str(), command_send.size()+1, 0);
            break;
        }
    }
    game->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::window_w, Game::window_h, false);
    while(game->running()){

        memset(buf, 0, 4096);
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if(bytesRecv == -1){
            cout<<"Connection issue"<<endl;
            break;
        }
        if(bytesRecv == 0){
            cout<<"Client disconnected"<<endl;
            break;
        }
        string command = string(buf, 0, bytesRecv);
        cout<<"Received: "<<command<<endl;
        send(clientSocket, buf, bytesRecv + 1, 0);

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }

    }
    close(clientSocket);
    game->clean();
}