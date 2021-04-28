#pragma once

#include "includes.hpp"

class Texture{
public:
	static SDL_Texture * LoadTexture(const char * fileName);
	static SDL_Texture * LoadTexture(SDL_Renderer * renderer, const char * texture);
	static SDL_Texture * LoadTexture(SDL_Surface * tempSurface);
	static SDL_Texture * LoadTexture(SDL_Renderer * renderer, SDL_Surface * tempSurface);
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);
	static void Draw(SDL_Renderer * renderer, SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);
};