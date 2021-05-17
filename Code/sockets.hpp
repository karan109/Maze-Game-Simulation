#pragma once

#include "Game.hpp"
#include "Texture.hpp"
#include "Button.hpp"

struct thread_data {
    int part;
};

int THREADS = 1; // Number of threads
void * temporal(void * arg);

char buf[4096];
int clientSocket, sock;
unsigned int frameStart;
int frameTime;
bool receive = true, sending = true;
int prevSend = 0;
int listening;
pthread_t threads[1];
struct thread_data data[1];
string command;
int create_server(){
	listening = socket(AF_INET, SOCK_STREAM, 0);
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
    // fcntl(listening, F_SETFL, fcntl(listening, F_GETFL) | O_NONBLOCK);
    return 0;
}
int wait_connect(){
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    clientSocket = accept(listening, (struct sockaddr *) & client, & clientSize);

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
    memset(buf, 0, 4096);
    cout<<"ok"<<endl;
    int bytesRecv = recv(clientSocket, buf, 4096, 0);
    cout<<"done"<<endl;
    if(bytesRecv == -1){
        cout<<"Connection issue"<<endl;
        return -1;
    }
    if(bytesRecv == 0){
        cout<<"Client disconnected"<<endl;
        return -1;
    }
    string command_rec = string(buf, 0, bytesRecv);
    // send(clientSocket, buf, bytesRecv + 1, 0);
    if(command_rec == "start"){
        srand(time(0));
        // Game::seed = rand()%100000;
        cout<<Game::seed<<endl;
        string command_send = to_string(Game::seed);
        int sendRes = send(clientSocket, command_send.c_str(), command_send.size()+1, 0);
        return 0;
    }
    return -1;
}
int create_client(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return -1;
    }
    int port = 54000;
    string ipAddress = "127.0.0.1"; // 122.177.240.201
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), & hint.sin_addr);
    int connectRes = connect(sock, (struct sockaddr * ) & hint, sizeof(hint));
    if(connectRes == -1){
        return -1;
    }
    return 0;
}
void wait_connect_client(){
    command = "start";
    int sendRes = send(sock, command.c_str(), command.size()+1, 0);
    if(sendRes == -1){
        cout<<"Could not send through server"<<endl;
    }
    memset(buf, 0, 4096);
    int bytesRecv = recv(sock, buf, 4096, 0);
    Game::seed = stoi(string(buf, bytesRecv));
}