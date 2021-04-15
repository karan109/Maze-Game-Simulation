#include "Maze.hpp"
#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Entities.hpp"

Entities * entities;
Player * player;
Maze * game_maze;
SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean){
	
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
	// vector<Player * > * Entities::players = new vector<Player *>(0);
	// vector<Wall * > * Entities::walls = new vector<Wall *>(0);
	entities = new Entities();
	player = new Player(SDL_Rect{0, 0, original_player_h, original_player_w}, SDL_Rect{0, 0, player_h, player_w});
	entities->Add(player);
	// Entities::Add(player);
	// entities->Add(player);
	game_maze = new Maze();
	game_maze->DrawMaze(false);
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
	game_maze->DrawMaze(true);
	player->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
