#pragma once

#include "includes.hpp"

class Texture{
public:
	static SDL_Texture * LoadTexture(const char * fileName);
	static SDL_Texture * LoadTexture(SDL_Surface * tempSurface);
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);
};