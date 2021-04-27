#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Drone.hpp"
#include "Monster.hpp"
#include "Stone.hpp"
#include "Snitch.hpp"
#include "Broom.hpp"


Maze * Game::game_maze = new Maze();
SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::event;

// Initialize entities object to store all entities
Entities * Game::entities = new Entities();
TTF_Font* Game::font;
// Constants
int Game::width;
int Game::height;
int Game::rows = 12;
int Game::cols = 25;
int Game::original_h = 32;
int Game::original_w = 32;
int Game::block_h = 32;
int Game::block_w = 32;
int Game::wall_thickness = 16;
bool Game::no_trap = true;
int Game::player_h = 30;
int Game::player_w = 30;
int Game::original_player_h = 32;
int Game::original_player_w = 32;
int Game::stone_w = 32;
int Game::stone_h = 32;
int Game::num_stones = 7;
int Game::menu = 100;
// int Game::seed = 0;
int Game::seed = time(0);
// int Game::response = 0;
// int Game::send = 0;
int Game::FPS = 60;
int Game::frameDelay = 1000 / FPS;
int Game::window_h = Game::wall_thickness + Game::menu + block_h * rows + (rows - 1) * wall_thickness;
int Game::window_w = 2 * Game::wall_thickness + block_w * cols + (cols - 1) * wall_thickness;

int Game::original_snitch_h = 414;
int Game::original_snitch_w = 874;


Mix_Music * Game::gMusic = nullptr;
Mix_Chunk * Game::gScratch = nullptr;
Mix_Chunk * Game::gHigh = nullptr;
Mix_Chunk * Game::gMedium = nullptr;
Mix_Chunk * Game::gLow = nullptr;

int Game::original_broom_h = 1274;
int Game::original_broom_w = 2393;
bool Game::broom_exists = 0;




Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean){
	Game::width = width;
	Game::height = height;
	int flags = 0;
	if(fullscrean){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 7, 33, 255, 255);
		}
		isRunning = true;
		if(TTF_Init()==-1) {
		    isRunning = false;
		}
		int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ){
            isRunning = false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            isRunning = false;
        }
	}
	else{
		isRunning = false;
	}
	srand(seed);
	font = TTF_OpenFont("../Fonts/arial.ttf", 100);
	Game::game_maze = new Maze();
	for(int i=0;i<num_stones;i++){
		stone = new Stone("../Images/stone.png", SDL_Rect{0, 0, stone_h, stone_w}, rand() % (Game::rows * Game::cols), 15, 10);
		entities->Add(stone);
	}
	
	drone = new Drone(SDL_Rect{0, 0, original_player_h, original_player_w}, 80);
	monster = new Monster(SDL_Rect{0, 0, original_player_h, original_player_w}, 50);
	snitch = new Snitch(SDL_Rect{0, 0, original_snitch_w, original_snitch_h}, 20);

	entities->Add(drone);
	entities->Add(monster);
	entities->Add(snitch);

	Game::game_maze->DrawMaze();

	gMusic = Mix_LoadMUS( "../Music/bgm.wav" );
	gScratch = Mix_LoadWAV( "../Music/wall_collide.wav" );
	// gHigh = Mix_LoadWAV( "../Music/high.wav" );
	// gMedium = Mix_LoadWAV( "../Music/medium.wav" );
	// gLow = Mix_LoadWAV( "../Music/low.wav" );

	// auto background = Texture::LoadTexture("../Images/background.jpg");
	// auto water = Texture::LoadTexture("../Images/water.png");
	// Texture::Draw(background, SDL_Rect{0, 0, 1920, 1080}, SDL_Rect{0, menu, width, height - menu});
	// Texture::Draw(water, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, 0, width, menu});
}
void Game::handleEvents(){
	SDL_PollEvent(& event);
	if(event.type == SDL_QUIT){
		isRunning = false;
	}
}
void Game::update(){
	for(auto & stone : * entities->stones){
		stone->Update();
	}
	for(auto & player : * entities->players){
		player->Update();
	}
	for(auto & remote : * entities->remotes){
		remote->Update();
	}
	for(auto & monster : * entities->monsters){
		monster->Update();
	}
	for(auto & drone : * entities->drones){
		drone->Update();
	}
	for(auto & snitch : * entities->snitches){
		snitch->Update();
	}
	for(auto & health : * entities->healths){
		health->Update();
	}


	if (SDL_GetTicks() >= 10000 and broom_exists == 0) {
		broom = new Broom(SDL_Rect{0, 0, original_broom_w, original_broom_h}, (Game::rows * Game::cols / 2));
		entities->Add(broom);
		broom_exists = 1;
	}

	for(auto & broom : * entities->brooms){
		broom->Update();
	}

}
void Game::render(){
	SDL_RenderClear(renderer);
	auto black = Texture::LoadTexture("../Images/black.png");
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, menu - wall_thickness, width, wall_thickness});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, menu, wall_thickness, height - menu});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{width - wall_thickness, menu, wall_thickness, height - menu});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, height - wall_thickness, width, wall_thickness});
	Game::game_maze->DrawMaze();
	for(auto & stone : * entities->stones){
		stone->Render();
	}
	for(auto & player : * entities->players){
		player->Render();
	}
	for(auto & remote : * entities->remotes){
		remote->Render();
	}
	for(auto & monster : * entities->monsters){
		monster->Render();
	}
	for(auto & drone : * entities->drones){
		drone->Render();
	}
	for(auto & snitch : * entities->snitches){
		snitch->Render();
	}
	for(auto & health : * entities->healths){
		health->Render();
	}

	for(auto & broom : * entities->brooms){
		broom->Render();
	}
	
	SDL_SetRenderDrawColor(renderer, 7, 33, 255, 255);
	SDL_RenderPresent(renderer);

}
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
