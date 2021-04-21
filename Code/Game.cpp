#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Drone.hpp"
#include "Monster.hpp"
#include "Stone.hpp"
Drone * drone;
Monster * monster;
Player * player;
Stone * stone;
Maze * Game::game_maze = new Maze();
SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::event;
Entities * Game::entities = new Entities();
int Game::width;
int Game::height;
int Game::rows = 20;
int Game::cols = 35;
int Game::original_h = 32;
int Game::original_w = 32;
int Game::block_h = 32;
int Game::block_w = 32;
int Game::wall_thickness = 5;
bool Game::no_trap = true;
int Game::player_h = 30;
int Game::player_w = 30;
int Game::original_player_h = 32;
int Game::original_player_w = 32;
int Game::stone_w = 32;
int Game::stone_h = 32;
int Game::num_stones = 7;

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else{
		isRunning = false;
	}
	srand(time(0));
	Game::game_maze = new Maze();
	for(int i=0;i<num_stones;i++){
		stone = new Stone("../Images/stone.png", SDL_Rect{0, 0, stone_h, stone_w}, rand() % (Game::rows * Game::cols), 15, 10);
		entities->Add(stone);
	}
	
	drone = new Drone(SDL_Rect{0, 0, original_player_h, original_player_w}, 100);
	monster = new Monster(SDL_Rect{0, 0, original_player_h, original_player_w}, 50);
	player = new Player(SDL_Rect{0, 0, original_player_h, original_player_w}, 0);
	drone->set_stones();
	monster->set_dest(player);
	entities->Add(drone);
	entities->Add(player);
	entities->Add(monster);
	Game::game_maze->DrawMaze();
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
	for(auto & monster : * entities->monsters){
		monster->Update();
	}
	for(auto & drone : * entities->drones){
		drone->Update();
	}
}
void Game::render(){
	SDL_RenderClear(renderer);
	Game::game_maze->DrawMaze();
	for(auto & stone : * entities->stones){
		stone->Render();
	}
	for(auto & player : * entities->players){
		player->Render();
	}
	for(auto & monster : * entities->monsters){
		monster->Render();
	}
	for(auto & drone : * entities->drones){
		drone->Render();
	}
	SDL_RenderPresent(renderer);
}
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
