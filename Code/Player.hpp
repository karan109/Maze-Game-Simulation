#pragma once

#include "Entity.hpp"
#include "Health.hpp"

class Broom;
class Player : public Entity{
public:
	Player(SDL_Rect srcR_param, int start, int number_param);
	Player(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param);
	Health * health_box, * static_health_box;
	void Update() override; // Update function
	void Delete();

	bool on_the_broom = 0;
	Broom * my_broom = nullptr;

};