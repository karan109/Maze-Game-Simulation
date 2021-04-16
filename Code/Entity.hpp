#pragma once

#include "includes.hpp"

class Entity{
public:
	static const int speed = 3;
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
	void Render();
	int xpos;
	int ypos;
protected:
	int xv;
	int yv;
	SDL_Rect srcR, destR;
private:
	SDL_Texture * objTexture;
};