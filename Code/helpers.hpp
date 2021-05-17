#include "sockets.hpp"
Game * game = nullptr;
bool quit = false;

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
    Game::font = TTF_OpenFont("../Fonts/arial.ttf", 100);
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
                    // Give message
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