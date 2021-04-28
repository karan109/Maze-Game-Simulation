#pragma once
#include "includes.hpp"

class Button{
public:
	Button(SDL_Rect destR_param, int thickness, string text);
	bool isInside(int x, int y);
	void Render(SDL_Renderer * renderer);
private:
	SDL_Rect destR;
	string text;
	int thickness;
};