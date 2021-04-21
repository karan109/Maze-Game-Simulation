#pragma once

#include "Entity.hpp"

class Automated : public Entity{
public:
	Automated(const char * texturesheet, SDL_Rect srcR_param, int start);
	void set_dest(int dest_param); // Set path to go to single node number
	void set_stones(); // Set path to go to all stones
protected:
	int dest; // final destination (not needed in case of stones)
	queue<int> path; // Paht as queue of node numbers
	int current; // Current node number of entity
	void print_path(); // Prints path for debugging
};