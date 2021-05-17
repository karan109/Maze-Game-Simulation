#pragma once

#include "Entity.hpp"
#include "Automated.hpp"
#include "Health.hpp"


class Monster : public Automated{
public:
	Monster(SDL_Rect srcR_param, int start, bool chase_start, int number_param);
	Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param, bool chase_start, int number_param);
	void Update();
	void Delete();
	void  switch_in_scared_mode();
	void  switch_in_not_scared_mode();
	void switch_modes();
	void normal_time_update();
	void scared_time_update();

	int normal_counter = 0;
	double normal_time = 0;
	int scared_counter = 0;
	double scared_time = 0;
	queue<int> seq;
	bool chase = 1;
	void set_target();
	void set_scary_target();
	void handle_spell_collisions();

	int spell_collision_counter = 0;
	int spell_collision_time = 0;
	bool spell_scared = 0;

	void spell_collision_time_update();
	void reset_spell_collision_time();

	void determine_scared(); 

	Health * health_box, * static_health_box;


};