#pragma once

#include "Entity.hpp"
#include "Health.hpp"

class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start);
	Health * health_box;
	void Update() override; // Update function
};