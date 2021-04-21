#pragma once

#include "Entity.hpp"

class Stone : public Entity{
public:
	Stone(const char * texturesheet, SDL_Rect srcR_param, int start, int height_param, int width_param);
	// void Update() override;
};