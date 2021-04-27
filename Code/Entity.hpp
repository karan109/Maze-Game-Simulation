#pragma once

#include "includes.hpp"

class Entity{
public:
	double speed = 3;
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
	virtual void Update();
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
	int health = 100;
	int counter = 0;
	int number;


	static bool in_sight(Entity * e1, Entity * e2);
	static int distance(Entity * e1, Entity * e2);
	static int is_frightened(Entity * e1, Entity * e2);

protected:
	int mag = 1; // Magnitude of velocity
	int xv; // x component of velocity
	int yv; // y component of velocity
	SDL_Rect srcR, destR; // destR is bounding box of entity
	SDL_Texture * objTexture; // Texture
};