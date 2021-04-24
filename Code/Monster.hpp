#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Monster : public Automated{
public:
	Monster(SDL_Rect srcR_param, int start);
	void Update() override;
	// void set_dest(Entity * target_param); // Monster requires an entity to follow and calculate path
private:
	// Entity * target;
};