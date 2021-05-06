#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Monster : public Automated{
public:
	Monster(SDL_Rect srcR_param, int start);
	Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param);
	void Update();
	int monster_retreat_node;
	bool player_is_scary;
	bool monster_is_scared;

	void  switch_in_scared_mode();
	void  switch_in_not_scared_mode();

	int switch_distance_scared;
	int switch_distance_not_scared;

};