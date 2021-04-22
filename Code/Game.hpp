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
	static int rows;
	static int cols;
	static int original_h;
	static int original_w;
	static int block_h;
	static int block_w;
	static int wall_thickness;
	static bool no_trap;
	static int player_h;
	static int player_w;
	static int original_player_h;
	static int original_player_w;
	static int stone_w;
	static int stone_h;
	static int num_stones;
	static int seed;
	static int FPS;
	static int frameDelay;
	static int window_h;
	static int window_w;
	static int response;
	static int send;
	Player * player1;
	Remote * player2;
	Drone * drone;
	Monster * monster;
	Stone * stone;

private:
	int ct = 0;
	bool isRunning;
	SDL_Window * window;
};