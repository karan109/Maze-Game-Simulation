#pragma once

#include "Entity.hpp"

class Automated : public Entity{
public:
	Automated(const char * texturesheet, SDL_Rect srcR_param, int start);
};