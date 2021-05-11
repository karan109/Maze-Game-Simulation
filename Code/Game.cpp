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
bool Game::isRunning = false;
// int Game::seed = 0;
int Game::seed = time(0);
// int Game::response = 0;
// int Game::send = 0;
int Game::FPS = 60;
int Game::frameDelay = 1000 / FPS;
int Game::window_h = Game::wall_thickness + Game::menu + block_h * rows + (rows - 1) * wall_thickness;
int Game::window_w = 2 * Game::wall_thickness + block_w * cols + (cols - 1) * wall_thickness;
int Game::N = Game::rows * Game::cols;

int Game::original_snitch_h = 414;
int Game::original_snitch_w = 874;
int Game::task;
string Game::player_name = "";
// <<<<<<< HEAD
Mix_Music * Game::gMusic = nullptr;
Mix_Chunk * Game::gScratch = nullptr;
Mix_Chunk * Game::gHigh = nullptr;
Mix_Chunk * Game::gMedium = nullptr;
Mix_Chunk * Game::gLow = nullptr;

int Game::original_broom_h = 1274;
int Game::original_broom_w = 2393;
// bool Game::broom_exists = 0;


int Game::global_counter = 0;
double Game::global_time = 0;
bool Game::paused = false;
int Game::pause_counter = 0;
double Game::pause_time = 0;



Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean){
	if(task == 2) no_trap = false;
	Game::width = width;
	Game::height = height;
	int flags = 0;
	if(fullscrean){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if(isRunning){
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
	}
	srand(seed);
	Game::game_maze = new Maze();
	if(Game::task == 2){
		for(int i=0;i<num_stones;i++){
			stone = new Stone("../Images/stone2.png", SDL_Rect{0, 0, 353, 300}, rand() % (Game::rows * Game::cols), 15, 15);
			entities->Add(stone);
		}
		drone = new Drone(SDL_Rect{144, 288, 72, 72}, 0);
		entities->Add(drone);
	}
	if(Game::task == 1){
		monster = new Monster(SDL_Rect{0, 0, 191, 161}, 10, 3, 100); // change to Game::rows * Game::cols - 1
		snitch = new Snitch(SDL_Rect{0, 0, original_snitch_w, original_snitch_h}, 20);
		entities->Add(monster);
		entities->Add(snitch);
	}
	Game::game_maze->DrawMaze();

	gMusic = Mix_LoadMUS( "../Music/bgm.wav" );
	gScratch = Mix_LoadWAV( "../Music/wall_collide.wav" ); //wall collision

}
void Game::handleEvents(){

	handle_quit_game();

	update_global_running_time();

}


void Game::handlePause() {

	handle_quit_game();

	update_global_paused_time();

	switch_pause();
}


void Game::handle_quit_game () {
	SDL_PollEvent(& event);
	if(event.type == SDL_QUIT){
		isRunning = false;
	}
}
void Game::update_global_running_time() {
	global_counter++;
	global_time = (double)global_counter / Game::FPS;
}

void Game::update_global_paused_time() {
	pause_counter++;
	pause_time = (double) pause_counter / Game::FPS;
}
void Game::switch_pause() {
	if (pause_time == 5) {
		paused = false;
		pause_counter = 0;
		pause_time = 0;
	}
}
void Game::Add_entities() {
	// add broom
	if(task == 1){
		if (global_time == 10) {
			int broom_starting_node = ( Game::rows/2 ) * (Game::cols) + (Game::cols/2);
			broom = new Broom(SDL_Rect{0, 0, original_broom_w, original_broom_h}, broom_starting_node);//(Game::rows * Game::cols / 2)
			entities->Add(broom);
			// broom_exists = 1;
		}
	}
}
void Game::update(){

	if (paused) return;

	Add_entities();


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

	for(auto & broom : * entities->brooms){
		broom->Update();
	}

// <<<<<<< HEAD
// =======


}
void Game::render(){
	SDL_RenderClear(renderer);
	if(task == 1){
		// auto background = Texture::LoadTexture("../Images/background2.jpg");
		// Texture::Draw(background, SDL_Rect{0, 0, 1280, 720}, SDL_Rect{0, 0, width, height});
	}
	else{
		// auto background = Texture::LoadTexture("../Images/bg2.webp");
		// Texture::Draw(background, SDL_Rect{0, 0, 400, 300}, SDL_Rect{0, 0, width, height});
	}
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
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if(task == 2){
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Simulation", SDL_Color{0, 0, 0, 255});
	    SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);
	    SDL_Rect Message_rect;
	    Message_rect.w = 300;
	    Message_rect.h = 50;
	    Message_rect.y = 10;
	    Message_rect.x = window_w / 2 - Message_rect.w / 2;
	    SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
	}

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


void Game::handle_collisions() {

	// what if collides with another player?
	// if collides with target then return
	for(auto & player: * Game::entities->players){
		for(auto & monster: * Game::entities->monsters){

			int dir = Collision::close_AABB(monster->getBB(), player->getBB(), monster->getXV(), monster->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {
				paused = 1;
			// if (Collision::happens(player, monster)) {
				// cout << 1 << endl;
				// xv = 0;	no cleanup
				if (player->scary) {
					// player has got to the monster
					// monster will vanish and start from beginning
					// player will continue
					// add a game pause where monster blinks and stuff happens?
					// Delete();
					monster->restart();		
				}
				else {
					//monster has got to the player
					// player will vanish and start from beginning.
					// monster will continue? not sure
					// monster will emit fire
					// monster will retreat?
					// handle game stuck case
					// change player health decrement 1 life
					// cout << "got ya bitch ";
					monster-> restart();
					player->restart();					
					return;
				}			
			}
			// else cout << 0 << endl;
		}
		// cout << Game::entities->brooms->size() << endl;

		for(auto & broom: * Game::entities->brooms){
			int dir = Collision::close_AABB(broom->getBB(), player->getBB(), broom->getXV(), broom->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {
				paused = 1;

				player->scary = 1; // transform the game when player is scary
				player->on_the_broom = 1;
				player->my_broom = broom;
				broom->caught = 1;
				broom->my_player = player;
			}
		}


		for(auto & snitch: * Game::entities->snitches){
			int dir = Collision::close_AABB(snitch->getBB(), player->getBB(), snitch->getXV(), snitch->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {
				paused = 1;

				//player has caught the snitch
				snitch->caught = 1;
				snitch-> transform();
				//increase lives of player
			}
		}






	}



	



	//monster and automated stuff collision

}