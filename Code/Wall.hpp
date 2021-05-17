#pragma once

#include "Entity.hpp"

class Wall : public Entity{
public:
	Wall(SDL_Rect srcR_param, SDL_Rect destR_param);
	void Update();
};