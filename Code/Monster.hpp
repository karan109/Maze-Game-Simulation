#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Monster : public Automated{
public:
	Monster(SDL_Rect srcR_param, int start);
	Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param);
	void Update();
};