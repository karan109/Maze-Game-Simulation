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
	void keepInside();
	pair<int, int> getCurrentBlockCoords();
	pair<int, int> getAutoBlockCoords();
	pair<int, int> getAutoBlockCoords(int block_num);
	void Render();
	int xpos;
	int ypos;
protected:
	int mag = 1;
	int xv;
	int yv;
	SDL_Rect srcR, destR;
private:
	SDL_Texture * objTexture;
};