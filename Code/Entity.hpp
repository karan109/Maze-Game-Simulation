#pragma once

#include "includes.hpp"

class Entity{
public:
	static const int speed = 1;
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
	void Render();
protected:
	int xpos;
	int ypos;
	int xv;
	int yv;
	SDL_Rect srcR, destR;
private:
	SDL_Texture * objTexture;
};