#pragma once

#include "includes.hpp"
#include "Entities.hpp"
#include "Maze.hpp"
class Game{

public:
	Game();
	~Game();
	void init(const char * title, int xpos, int ypos, int width, int height, bool fullscrean);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running(){
		return isRunning;
	}
	static SDL_Renderer * renderer;
	static SDL_Event event;
	static Entities * entities;
	static Maze * game_maze;
	static int width;
	static int height;

private:
	int ct = 0;
	bool isRunning;
	SDL_Window * window;
};