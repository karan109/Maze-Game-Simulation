#pragma once

#include "Entity.hpp"
#include "Health.hpp"

// class Broom;
class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start, int number_param);
	Player(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param, int type_param = 1);
	Health * health_box, * static_health_box;
	void Update(); // Update function
	void Delete();

	
	
	double boost_time_limit;
	double boost_speed;
	void update_boost();
	void boost_on();
	void boost_off();
	void update_boost_time_left();
	bool casting_conditions();
	// bool release_conditions();
	void cast_spell();

	double health_dps;

	void handle_spell_collisions();
	int type;
	string player_name = "";
	// Broom * my_broom = nullptr;
	void animated_stuff();

};