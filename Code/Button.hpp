#pragma once
#include "includes.hpp"

class Button{
public:
	Button(SDL_Rect destR_param, int thickness, string text);
	Button(SDL_Renderer * renderer, string character_param, SDL_Rect srcR_param, SDL_Rect destR_param);
	bool isInside(int x, int y);
	void Render(SDL_Renderer * renderer);
	bool show = false;
private:
	SDL_Rect srcR, destR;
	SDL_Texture * objTexture;
	string text;
	int thickness = 2;
	bool image = false;
	string character = "";
};