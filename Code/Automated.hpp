#pragma once

#include "Entity.hpp"

class Automated : public Entity{
public:

Automated(const char * texturesheet, SDL_Rect srcR_param, int start);



void Update();

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
void set_at_centre();






protected:
	// int dest; // final destination (not needed in case of stones)
	queue<int> path; // Path as queue of node numbers
	int current; // Current node number of entity
	void print_path(); // Prints path for debugging
};