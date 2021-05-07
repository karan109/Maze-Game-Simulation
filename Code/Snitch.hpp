#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Snitch : public Automated{
public:
	Snitch(SDL_Rect srcR_param, int start);
	void Update();
	void Delete();



	SDL_Texture * vanish_texture;
	SDL_Texture * snitch_texture;

	int disapparation_time;
	int blinking_time;
	int vanish_time;
	int vanish_counter;
	int apparation_time;

	bool vanish;
	bool exists = true;	
	bool disappearing_mode = 1;
	int switch_distance;

	void switch_mode();

private:

};