#include "Game.hpp"
#include "Texture.hpp"
#include "Button.hpp"
Game * game = nullptr;

int main(int argc, char* argv[]){

    unsigned int frameStart;
    int frameTime;


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
    SDL_Window * window = SDL_CreateWindow("Start Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    auto background = Texture::LoadTexture(renderer, "../Images/background2.jpg");
    int margin = 30;
    int button_width = 150;
    int button_height = 40;
    int sprite_width = 70;
    int sprite_height = 70;
    int sprite_margin = 50;
    Button * button1 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height, button_width, button_height}, 2, "Start");
    Button * button2 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height + button_height + margin, button_width, button_height}, 2, "Task 1");
    Button * button3 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height + 2 * (button_height + margin), button_width, button_height}, 2, "Task 2");
    Button * button4 = new Button(renderer, "harry", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 - sprite_width / 2, 200, sprite_width, sprite_height});
    Button * button5 = new Button(renderer, "hermione", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 - sprite_width * 3 / 2 - sprite_margin, 200, sprite_width, sprite_height});
    Button * button6 = new Button(renderer, "ron", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 + sprite_width / 2 + sprite_margin, 200, sprite_width, sprite_height});
    while(true){
        SDL_RenderClear(renderer);
        Texture::Draw(renderer, background, SDL_Rect{0, 0, 1280, 720}, SDL_Rect{0, 0, 1000, 600});
        SDL_Event event;
        SDL_PollEvent(& event);
        if(event.type == SDL_QUIT){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            Mix_Quit();
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return 0;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState( &x, &y );
                if(button1->isInside(x, y)){
                    Game::task = 1;

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
                            cout<<Game::seed<<endl;
                            string command_send = to_string(Game::seed);
                            int sendRes = send(clientSocket, command_send.c_str(), command_send.size()+1, 0);
                            break;
                        }
                    }

                    break;
                }
                else if(button2->isInside(x, y)){
                    Game::task = 1;

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
                            cout<<Game::seed<<endl;
                            string command_send = to_string(Game::seed);
                            int sendRes = send(clientSocket, command_send.c_str(), command_send.size()+1, 0);
                            break;
                        }
                    }

                    break;
                }
                else if(button3->isInside(x, y)){
                    Game::task = 2;
                    break;
                }
                else if(button4->isInside(x, y)){
                    button4->show = true;
                    button5->show = false;
                    button6->show = false;
                    Game::player_name = "harry1";
                }
                else if(button5->isInside(x, y)){
                    button4->show = false;
                    button5->show = true;
                    button6->show = false;
                    Game::player_name = "hermione";
                }
                else if(button6->isInside(x, y)){
                    button4->show = false;
                    button5->show = false;
                    button6->show = true;
                    Game::player_name = "ron";
                }
            }
        }
        if(Game::player_name == "") Game::player_name = "harry1";
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, "Game", SDL_Color{255, 255, 0, 255});
        SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

        SDL_Rect Message_rect;
        Message_rect.w = 150;
        Message_rect.h = 50;
        Message_rect.y = 10;
        Message_rect.x = 500 - Message_rect.w / 2;
        SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
        button1->Render(renderer);
        button2->Render(renderer);
        button3->Render(renderer);
        button4->Render(renderer);
        button5->Render(renderer);
        button6->Render(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

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
    while(game->running()){
        if (Game::response < 0) Game::response = 0;
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
        Game::response = stoi(command);
        // cout<<Game::response<<endl;
        int sendRes = send(clientSocket, to_string(Game::send).c_str(), command.size()+1, 0);
        if(sendRes == -1){
            cout<<"Could not send through server"<<endl;
        }

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