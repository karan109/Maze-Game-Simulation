#pragma once

#include "Entity.hpp"

class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, SDL_Rect destR_param);
	void Update() override;
	int getBlock();
	bool getRight();
	bool getLeft();
	bool getUp();
	bool getDown();
};