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

	void handle_quit_game ();
	void update_global_running_time();
	void Add_entities();
	void handle_collisions();
	static bool paused;
	// void handlePause();
	void update_global_paused_time();
	void switch_pause();


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
	static int menu;
	static TTF_Font* font;
	static bool isRunning;
	static int task;
	static string player_name;
	static int N;
	// static int response;
	// static int send;

	// static int drone_starting_node = 
	// static int monster_starting_node = 
	// static int snitch_starting_node = 

	static int original_snitch_h;
	static int original_snitch_w;

	static int original_broom_h;
	static int original_broom_w;
	// static bool broom_exists;
	Broom * broom;

	Player * player1;
	// Player * player2;

	// Remote * player2;
	Drone * drone;
	Monster * monster;
	Stone * stone;
	Snitch * snitch;

	static Mix_Music * gMusic;
	static Mix_Chunk * gScratch;
	static Mix_Chunk * gHigh;
	static Mix_Chunk * gMedium;
	static Mix_Chunk * gLow;

	static int global_counter;
	static double global_time;

	static int pause_counter;
	static double pause_time;





private:
	int ct = 0;
	SDL_Window * window;
};