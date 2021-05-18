#pragma once

#include "Entity.hpp"

class Health : public Entity{
public:
	Health(SDL_Rect srcR_param, Entity * target_param, bool move_param, bool show_param = true);
	void Update();
	void Render();
	SDL_Texture * white, * black, * snitch, *broom, * cloak;
	Entity * target;
	int length;
	int full = 100;
	bool move, show;
	SDL_Rect figure;
	int counter = 0;
};