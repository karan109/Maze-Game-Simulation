#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	speed = 2.5;
	set_mode(2);
}

void Snitch::Update() {

	// srand(Game::seed); //already done in Game.cpp?
	
	counter++;

	if(counter == Game::FPS * disapparation_time){

		counter = 0;

		// set new position and velocity/path
		int starting_node = rand() % (Game::rows * Game::cols);
		set_starting_node(starting_node);
		set_path_mode2();

	}

	Automated::Update();

}