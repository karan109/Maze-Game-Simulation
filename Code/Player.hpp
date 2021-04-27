#pragma once

#include "Entity.hpp"
#include "Health.hpp"

class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start, int number_param);
	Health * health_box, * static_health_box;
	void Update() override; // Update function
};