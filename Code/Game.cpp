#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Drone.hpp"

Drone * player;
Maze * Game::game_maze = new Maze();
SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::event;
Entities * Game::entities = new Entities();
int Game::width;
int Game::height;

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
	player = new Drone(SDL_Rect{0, 0, original_player_h, original_player_w}, SDL_Rect{0, 0, player_h, player_w}, 499);
	entities->Add(player);
	Game::game_maze->DrawMaze();
}
void Game::handleEvents(){
	SDL_PollEvent(& event);
	if(event.type == SDL_QUIT){
		isRunning = false;
	}
}
void Game::update(){
	player->Update();
}
void Game::render(){
	SDL_RenderClear(renderer);
	Game::game_maze->DrawMaze();
	player->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
