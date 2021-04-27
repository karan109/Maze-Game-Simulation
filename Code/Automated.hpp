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
// bool reached = false;
void set_dest(int dest_param);
void Update1();



// mode = 2
void set_path_mode2(int x);
void Update2();




//mode = 3
bool reached = false;
void set_stones();
void Update3();







protected:
	// int dest; // final destination (not needed in case of stones)
	queue<int> path; // Path as queue of node numbers
	int current; // Current node number of entity
	void print_path(); // Prints path for debugging
};