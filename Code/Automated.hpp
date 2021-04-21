#pragma once

#include "Entity.hpp"

class Automated : public Entity{
public:
	Automated(const char * texturesheet, SDL_Rect srcR_param, int start);
	void set_dest(int dest_param);
	void set_stones();
protected:
	int dest;
	queue<int> path;
	int current;
	void print_path();
};