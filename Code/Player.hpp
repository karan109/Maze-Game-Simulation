#pragma once

#include "Entity.hpp"

class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start);
	void Update() override;
};