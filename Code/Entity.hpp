#pragma once

#include "includes.hpp"

class Entity{
public:
	Entity(const char * texturesheet, int x, int y);
	~Entity();
	void Update();
	void Render();
private:
	int xpos;
	int ypos;
	int xv;
	int yv;
	const int speed = 3;
	int height = 32;
	int width = 32;
	int scale = 1;
	SDL_Texture * objTexture;
	SDL_Rect srcR, destR;
};