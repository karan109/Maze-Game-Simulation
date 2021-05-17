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
	Player * player;
	Drone * drone;
	Monster * monster;
	Stone * stone;
	Snitch * snitch;

	static Mix_Music * gMusic;
	static Mix_Chunk * gScratch;
	static Mix_Chunk * gHigh;
	static Mix_Chunk * gMedium;
	static Mix_Chunk * gLow;


	static double player_original_speed;
	static double player_boost_speed;
	static double player_boost_time_limit;


	static double monster_original_speed;
	static double snitch_original_speed;




	Broom * collided_broom = nullptr;
	Player * collided_player = nullptr;
	Monster * collided_monster = nullptr;
	Snitch * collided_snitch = nullptr;

	string collision_code = "";


	void handle_quit_game ();
	void Add_entities();



	static int global_counter;
	static double global_time;

	static int pause_counter;
	static double pause_time;
	static bool paused;
	static double global_pause_time_variable;


	static int collision_counter;
	static double collision_time;
	static bool collision_happened;


	void update_global_running_time();
	void update_global_pause_time();
	void update_global_collision_time();

	void switch_collision();
	void switch_pause();


	void handle_collisions();
	void start_game_collision ();
	void collision_updates();
	bool resume_safely ();
	void reset_collided_entities();
	void collision_pause ();


	static void game_pause (double t);


	static int monster1_starting_node;
	static int monster2_starting_node;
	static int player1_starting_node;
	static int broom_starting_node;
	static int snitch_starting_node;



	static int broom_apparatation_time;
	static int broom_disapparation_time;



	static double player_monster_collision_pause;
	static double player_snitch_collision_pause;
	static double player_broom_collision_pause;

	static int monster_cycle_time;
	static bool spacebar_pressed;

	static void print_queue(queue<int>);

	static queue<int> seq_generator(double p, bool chase, int sampling_time);
	void add_monster(int start, double p, bool chase, int number_param);
	void add_player(int start, int number_param);
	void add_snitch(int start);
	void add_broom(int appear_time, int start);

	static double player_health_decrement_per_second;

private:
	int ct = 0;
	SDL_Window * window;
};