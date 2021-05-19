#include "sockets.hpp"
Game * game = nullptr;
bool quit = false;
string delim = ",";
void key_testing() {
    if(Game::event.type == SDL_KEYDOWN){
        auto key = Game::event.key.keysym.sym;
        if(key == SDLK_SPACE)  {
            if (Game::spacebar_pressed == 0) {
                Game::spacebar_pressed = 1;
            }
        }
    }

    if(Game::event.type == SDL_KEYUP){
        auto key = Game::event.key.keysym.sym;
        if(key == SDLK_SPACE)  {
            if (Game::spacebar_pressed == 1) {
                Game::spacebar_pressed = 0;
            }
        }
    }
    if(Game::weapon_rec == 1 and Game::remote_spacebar_pressed == 0){
        Game::remote_spacebar_pressed = 1;
    }
    if(Game::weapon_rec == -1 and Game::remote_spacebar_pressed == 1){
        Game::remote_spacebar_pressed = 0;
    }
}
string info(Entity * ent){
    return to_string(ent->xpos)+","+to_string(ent->ypos)+","+to_string(ent->xv)+","+to_string(ent->yv)+","+to_string(ent->health);
}
void getinfo(Entity * ent, int ind, vector<string> & process){
    ent->xpos = stoi(process[ind++]);
    ent->ypos = stoi(process[ind++]);
    ent->xv = stoi(process[ind++]);
    ent->yv = stoi(process[ind++]);
    ent->health = stod(process[ind++]);
}
void init(){
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
    Game::font = TTF_OpenFont("../Fonts/harry.ttf", 100);
}
int main_menu(){
    unsigned int frameStart;
    int frameTime;
    SDL_Window * window = SDL_CreateWindow("Start Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    auto background = Texture::LoadTexture(renderer, "../Images/bg3.jpg");
    int margin = 30;
    int button_width = 150;
    int button_height = 40;
    int sprite_width = 70;
    int sprite_height = 70;
    int sprite_margin = 50;
    Button * button1 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height, button_width, button_height}, 2, "Single Player");
    Button * button2 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height + button_height + margin, button_width, button_height}, 2, "Server");
    Button * button7 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height + 2 * (button_height + margin), button_width, button_height}, 2, "Client");
    Button * button3 = new Button(SDL_Rect{500 - button_width / 2, 250 + margin + sprite_height + 3 * (button_height + margin), button_width, button_height}, 2, "Task 2");
    Button * button4 = new Button(renderer, "harry", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 - sprite_width / 2, 200, sprite_width, sprite_height});
    Button * button5 = new Button(renderer, "hermione", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 - sprite_width * 3 / 2 - sprite_margin, 200, sprite_width, sprite_height});
    Button * button6 = new Button(renderer, "ron", SDL_Rect{32 * 7, 32 * 4, 32, 32}, SDL_Rect{500 + sprite_width / 2 + sprite_margin, 200, sprite_width, sprite_height});
    bool conn = false, wait = false;
    while(true){
        if(conn ){
            if(wait_connect()==0) break;
        }
        frameStart = SDL_GetTicks();
        SDL_RenderClear(renderer);
        Texture::Draw(renderer, background, SDL_Rect{0, 0, 533, 300}, SDL_Rect{0, 0, 1000, 600});
        SDL_Event event;
        SDL_PollEvent(& event);
        if(event.type == SDL_QUIT){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            Mix_Quit();
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            quit = true;
            break;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState( &x, &y );
                if(button1->isInside(x, y)){
                    Game::task = 1;
                    break;
                }
                else if(button2->isInside(x, y) and !wait){
                    Game::task = 1;
                    if(create_server()<0) return -1;
                    conn = true;
                    wait = true;
                    Game::server = true;
                    // break;
                }
                else if(button7->isInside(x, y)){
                    Game::task = 1;
                    if(create_client() < 0) continue;
                    Game::client = true;
                    wait_connect_client();
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
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, "Harry Potter and the Deathly Hallows", SDL_Color{255, 255, 0, 255});
        SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

        SDL_Rect Message_rect;
        Message_rect.w = 500;
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
        button7->Render(renderer);
        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
void server_work(){
    if (Game::response < 0) Game::response = 0;
    if (Game::weapon_rec < 0) Game::weapon_rec = 0;
    int sent = Game::send;
    int remain_monster = 0;
    if(game->monster1 != nullptr) remain_monster++;
    if(game->monster2 != nullptr) remain_monster++;
    string pos = info(game->player1)+","+to_string(Game::weapon)+","+to_string(remain_monster);
    if(game->monster1 != nullptr) pos += ",1";
    if(game->monster2 != nullptr) pos += ",2";
    if(game->monster1 != nullptr){
        pos += ","+info(game->monster1);
    }
    if(game->monster2 != nullptr){
        pos += ","+info(game->monster2);
    }
    if(game->snitch != nullptr){
        pos += ",1,"+info(game->snitch);
    }
    else{
        pos += ",0";
    }
    int sendRes = send(clientSocket, pos.c_str(), pos.size()+1, 0);
    if(sendRes == -1){
        // cout<<"Could not send through server"<<endl;
    }
    prevSend = sent;
    memset(buf, 0, 4096);
    int bytesRecv = recv(clientSocket, buf, 4096, 0);
    if(bytesRecv == -1){
        // cout<<"Connection issue"<<endl;
    }
    if(bytesRecv == 0){
        // cout<<"Client disconnected"<<endl;
    }
    string command = string(buf, 0, bytesRecv);
    if(command.size() == 0) return;
    if(command == "quit"){
        Game::isRunning = false;
        Game::win = true;
        return;
    }
    
    vector<string> process;
    tokenize(command, delim, process);
    game->player2->xpos = stoi(process[0]);
    game->player2->ypos = stoi(process[1]);
    game->player2->xv = stoi(process[2]);
    game->player2->yv = stoi(process[3]);
    game->player2->health = stod(process[4]);
    Game::weapon_rec = stoi(process[5]);
}
void client_work(){
    if (Game::response < 0) Game::response = 0;
    if (Game::weapon_rec < 0) Game::weapon_rec = 0;
    string command = to_string(Game::send);
    string pos = info(game->player1)+","+to_string(Game::weapon);
    int sent = Game::send;
    int sendRes = send(sock, pos.c_str(), pos.size()+1, 0);
    if(sendRes == -1){
        // cout<<"Could not send through server"<<endl;
    }
    prevSend = stoi(command);
    memset(buf, 0, 4096);
    int bytesRecv = recv(sock, buf, 4096, 0);
    string response = string(buf, bytesRecv);
    if(response.size() == 0) return;
    if(response[0] == 'q'){
        Game::isRunning = false;
        Game::win = true;
        return;
    }
    vector<string> process;
    tokenize(response, delim, process);
    getinfo(game->player2, 0, process);
    Game::weapon_rec = stoi(process[5]);
    int num_monsters = stoi(process[6]);
    if(num_monsters == 1){
        if(stoi(process[7]) == 1){
            getinfo(game->monster1, 8, process);
        }
        else{
            getinfo(game->monster2, 8, process);
        }
        if(stoi(process[13]) == 1){
            getinfo(game->snitch, 14, process);
        }
    }
    else if(num_monsters == 2){
        getinfo(game->monster1, 9, process);
        getinfo(game->monster2, 14, process);
        if(stoi(process[19]) == 1){
            getinfo(game->snitch, 20, process);
        }
    }
    else{
        if(stoi(process[7]) == 1){
            getinfo(game->snitch, 8, process);
        }
    }
}
int winning_message(){
    unsigned int frameStart;
    int frameTime;
    SDL_Window * window = SDL_CreateWindow("Epilogue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    string message;
    auto background = Texture::LoadTexture(renderer, "../Images/voldy.png");
    if(Game::win == 1){
        background = Texture::LoadTexture(renderer, "../Images/dumbledore.png");
    }
    auto harry = Texture::LoadTexture(renderer, "../Images/harrywin.png");
    auto ron = Texture::LoadTexture(renderer, "../Images/ronwin.png");
    auto hermione = Texture::LoadTexture(renderer, "../Images/hermionewin.png");
    auto hallow = Texture::LoadTexture(renderer, "../Images/hallow2.png");
    SDL_Texture * Character;
    string player_name;
    if(Game::player_name == "harry1"){Character = harry; player_name = "Harry";}
    else if(Game::player_name == "ron"){Character = ron; player_name = "Ron";}
    else{Character = hermione; player_name = "Hermione";}
    double scale = 0;
    int dumbw = 200, dumbh = 500;
    int ct = 0, ct2 = 0, ct3 = 0;
    int t = 5;
    while(true){
        scale = min((double)ct/(t * Game::FPS), (double)1);
        int tempw = scale * dumbw, temph = scale * dumbh;
        frameStart = SDL_GetTicks();
        SDL_RenderClear(renderer);
        if(ct2 == (t+1) * Game::FPS){
            Texture::Draw(renderer, Character, SDL_Rect{0, 0, 200, 500}, SDL_Rect{600, 150, 160, 400});
        }
        if(ct3 == (t+2) * Game::FPS){
            message = "Well done, "+player_name+"!";
            if(Game::win == 0) message = "You lose, "+player_name+"!";
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, message.c_str(), SDL_Color{0,0,0,255});
            SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

            SDL_Rect Message_rect;
            int digits = message.size();
            Message_rect.w = 15 * digits;
            Message_rect.h = 20;
            Message_rect.y = 20;
            Message_rect.x = 400 - Message_rect.w/2;
            SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
        }
        Texture::Draw(renderer, hallow, SDL_Rect{0, 0, 514, 485}, SDL_Rect{20, 300 - 150, 300, 300});
        Texture::Draw(renderer, background, SDL_Rect{0, 0, 200, 500}, SDL_Rect{400-tempw/2 + 20, 300-temph/2, tempw, temph});
        SDL_Event event;
        SDL_PollEvent(& event);
        if(event.type == SDL_QUIT){
            quit = true;
            break;
        }
        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if(Game::frameDelay > frameTime){
            SDL_Delay(Game::frameDelay - frameTime);
        }
        if(ct < t * Game::FPS) ct++;
        else ct = t * Game::FPS;
        if(ct2 < (t+1) * Game::FPS) ct2++;
        else ct2 = (t+1) * Game::FPS;
        if(ct3 < (t+2) * Game::FPS) ct3++;
        else ct3 = (t+2) * Game::FPS;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}