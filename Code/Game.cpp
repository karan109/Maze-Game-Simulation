#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Drone.hpp"
#include "Monster.hpp"

Drone * drone;
Monster * monster;
Player * player;
Maze * Game::game_maze = new Maze();
SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::event;
Entities * Game::entities = new Entities();
int Game::width;
int Game::height;
int Game::rows = 10;
int Game::cols = 15;
int Game::original_h = 32;
int Game::original_w = 32;
int Game::block_h = 32;
int Game::block_w = 32;
int Game::wall_thickness = 32;
bool Game::no_trap = true;
int Game::player_h = 30;
int Game::player_w = 30;
int Game::original_player_h = 32;
int Game::original_player_w = 32;

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
	Game::game_maze = new Maze();
	drone = new Drone(SDL_Rect{0, 0, original_player_h, original_player_w}, 100);
	monster = new Monster(SDL_Rect{0, 0, original_player_h, original_player_w}, 50);
	player = new Player(SDL_Rect{0, 0, original_player_h, original_player_w}, 0);
	drone->set_dest(rows * cols - 1);
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
