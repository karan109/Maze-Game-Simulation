#pragma once

#include "includes.hpp"

class Entity{
public:
	double speed = 3;
	Entity();
	Entity(const char * texturesheet, SDL_Rect srcR_param, int start);
	Entity(const char * texturesheet, SDL_Rect srcR_param, SDL_Rect destR_param);
	~Entity();
	int getX();
	int getY();
	int getXV();
	int getYV();
	void setX(int x);
	void setY(int y);
	void setXV(int xv_param);
	void setYV(int yv_param);
	SDL_Rect getBB();
	

	// not virtual anymore
	void Update();
	




	int getBlock();
	bool getRight();
	bool getLeft();
	bool getUp();
	bool getDown();

	bool can_go_right(int block_num);
	bool can_go_left(int block_num);
	bool can_go_up(int block_num);
	bool can_go_down(int block_num);

	bool is_inside_node(); 

	void keepInside();
	void set_starting_node(int start);

	pair<int, int> getCurrentBlockCoords();
	pair<int, int> getAutoBlockCoords();
	pair<int, int> getAutoBlockCoords(int block_num);
	virtual void Render();
	int xpos; // x coordinate
	int ypos; // y coordinate
	bool showHealth;
	double health = 100;

	int number;
	bool animated = false;
	int frames = 0;
	int animate_speed = 100;
	int face = 3;
	int wall_ct = 0;
	static bool in_sight(Entity * e1, Entity * e2);
	static int distance(Entity * e1, Entity * e2);
	static int is_frightened(Entity * e1, Entity * e2);

	bool scared = 0;
	bool scary = 0;
	int start_node;
	int retreat_node;
	bool caught = 0;

	// void set_pos_at_centre();
	// void set_pos (int start);
	// void set_velocity_zero();
	// void restart();


	void change_objTexture( SDL_Texture * tex ,SDL_Rect srcR_param, SDL_Rect destR_param);
	void change_objTexture( const char * texturesheet ,SDL_Rect srcR_param, SDL_Rect destR_param);

	int counter = 0;
	int entity_counter = 0;
	double entity_time = 0;
	void time_update();

	bool collided = 0;

// --------------------------------------------------FROM AUTOMATED---------------------------------------------
int mode;
// get_mode, set_mode etc
void set_mode(int mode_id, Entity * target_param);
void set_mode(int mode_id, int dest_param);
void set_mode(int mode_id);
void set_mode_id(int mode_id);


// mode = 0
Entity * target;
void set_dest(Entity * target_param);
void Update0();


// mode = 1
int dest;
bool scatter_reached = false;
void set_dest(int dest_param);
void Update1();



// mode = 2
void set_path_mode2();
void Update2();


// mode = 3
Entity * scary_target;
void set_path_mode3(Entity * scary_target);
void Update3();



//mode = 4
bool drone_reached = false;
void set_stones();
void Update4();


bool change_mode(int mode_id);
void empty_the_path();
bool is_at_centre();
void set_pos_at_centre();
void set_pos(int start);


void handle_wall_collisions();

int getNext();

int manhattan_distance(); 
int manhattan_distance_player(); 


void switch_next(int current, int next);

void update_position();

void set_velocity_zero();

void restart();

int switch_dir(int temp_dir, int current);

void print_path(); // Prints path for debugging

queue<int> path; // Path as queue of node numbers
int current; 

// player mode = -1
void Update_player();
void Update_remote();

int original_mode;
double original_speed;
int mode_before_collision;

void start_collision();
void resume_after_collision();

// bool casting_conditions();
// void cast_spell();
void handle_spell_collisions();


// ---------------------------------------------------------------------------------------------------------------------------------

Entity * nearest_player ();

bool spell_collision = 0;

void increase_health(double x);
void decrease_health(double x);

int prev = -1;
int smooth_turn_distance();
int lives = 1;



	int mag = 1; // Magnitude of velocity
	int xv; // x component of velocity
	int yv; // y component of velocity
	SDL_Rect srcR, destR; // destR is bounding box of entity
	SDL_Texture * objTexture; // Texture
};