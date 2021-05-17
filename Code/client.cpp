#include "Game.hpp"
#include "Texture.hpp"
#include "Button.hpp"
Game * game = nullptr;
struct thread_data {
    int part;
};

void tokenize(std::string const &str, string delim,
            std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim.c_str());
    while (token != nullptr)
    {
        out.push_back(string(token));
        token = strtok(nullptr, delim.c_str());
    }
}

int THREADS = 1; // Number of threads
void * temporal(void * arg);

char buf[4096];
int sock;
unsigned int frameStart;
int frameTime;
bool receive = true, sending = true;
int prevSend = 0;
int main(int argc, char* argv[]){

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
                    command = "start";
                    int sendRes = send(sock, command.c_str(), command.size()+1, 0);
                    if(sendRes == -1){
                        cout<<"Could not send through server"<<endl;
                    }
                    memset(buf, 0, 4096);
                    int bytesRecv = recv(sock, buf, 4096, 0);
                    Game::seed = stoi(string(buf, bytesRecv));
                    break;
                }
                else if(button2->isInside(x, y)){
                    Game::task = 1;
                    command = "start";
                    int sendRes = send(sock, command.c_str(), command.size()+1, 0);
                    if(sendRes == -1){
                        cout<<"Could not send through server"<<endl;
                    }
                    memset(buf, 0, 4096);
                    int bytesRecv = recv(sock, buf, 4096, 0);
                    Game::seed = stoi(string(buf, bytesRecv));
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

    cout<<Game::seed<<endl;
    // Game::task = 1;
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


    pthread_t threads[THREADS];

    struct thread_data data[THREADS];
    
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
    close(sock);
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
        string command = to_string(Game::send);
        string pos = to_string(game->player1->xpos)+","+to_string(game->player1->ypos)+","+to_string(game->player1->xv)+","+to_string(game->player1->yv);
        int sendRes = send(sock, pos.c_str(), pos.size()+1, 0);
        if(sendRes == -1){
            cout<<"Could not send through server"<<endl;
        }
        cout<<sendRes<<endl;
        prevSend = stoi(command);
        memset(buf, 0, 4096);
        int bytesRecv = recv(sock, buf, 4096, 0);
        string response = string(buf, bytesRecv);
        vector<string> process;
        tokenize(response, delim, process);
        game->player2->xpos = stoi(process[0]);
        game->player2->ypos = stoi(process[1]);
        game->player2->xv = stoi(process[2]);
        game->player2->yv = stoi(process[3]);
        // Game::response = stoi(response);
        receive = true;
    }
    else{
        
    }
    return (void *) 0;
}