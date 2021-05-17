#pragma once

#include "Entity.hpp"
#include "Health.hpp"

class Remote : public Entity{
public:
	Remote(SDL_Rect srcR_param, int start, int number_param);
	Remote(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param);
	Health * health_box, * static_health_box;
	void Update(); // Update function
};