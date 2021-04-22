#pragma once

#include "Entity.hpp"

class Remote : public Entity{
public:
	Remote(SDL_Rect srcR_param, int start);
	void Update() override; // Update function
};