#pragma once

#include "Entity.hpp"
#include "Health.hpp"

// class Broom;
class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start, int number_param);
	Player(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param);
	Health * health_box, * static_health_box;
	void Update(); // Update function
	void Delete();

	bool boost = 0;
	double boost_time_left = 0;
	double boost_time_limit;
	double boost_speed;
	void update_boost();
	void boost_on();
	void boost_off();
	void update_boost_time_left();

	// Broom * my_broom = nullptr;

};