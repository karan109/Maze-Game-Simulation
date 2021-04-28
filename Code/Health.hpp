#pragma once

#include "Entity.hpp"

class Health : public Entity{
public:
	Health(SDL_Rect srcR_param, Entity * target_param, bool move_param);
	void Update() override;
	void Render() override;
	SDL_Texture * white, * black;
	Entity * target;
	int length;
	int full = 100;
	bool move;
};