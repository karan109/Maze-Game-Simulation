#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Monster : public Automated{
public:
	Monster(SDL_Rect srcR_param, int start);
	Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param);
	void Update();
	void Delete();
	void  switch_in_scared_mode();
	void  switch_in_not_scared_mode();
	void switch_modes();
};