#include "Maze.hpp"
#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"

Entity * player;
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
	player = new Entity("../Images/man.png", 0, 0);
	game_maze = new Maze();
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
	game_maze->DrawMaze();
	player->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
