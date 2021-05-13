#pragma once

#include "Entity.hpp"

// class Player;
class Broom : public Entity{
public:
	Broom(SDL_Rect srcR_param, int start);

	void Update();
	void Delete();


	SDL_Texture * vanish_texture;
	SDL_Texture * broom_texture;


	int disapparation_time;
	int blinking_time;
	int vanish_time;
	int vanish_counter;
	int apparation_time;

	bool vanish;
	bool exists = true;	

	Player * my_player = nullptr;

private:

};