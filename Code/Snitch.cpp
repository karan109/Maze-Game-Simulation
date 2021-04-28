#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Texture.hpp"

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	speed = 2.5;
	// scary_target = nullptr;
	set_mode(2);
	vanish_texture = Texture::LoadTexture("../Images/water.png");
	snitch_texture = Texture::LoadTexture("../Images/snitch.png");

	vanish_counter = 0;
	vanish = 0;
	
	blinking_time = Game::FPS * 18;
	disapparation_time = Game::FPS * 20;
	// apparation_time = Game::FPS * 52;
	vanish_time = Game::FPS * 0.1;

	disappearing_mode = 1;
	switch_distance = 15;


}

void Snitch::switch_mode() {
	if (distance(this, scary_target) <= switch_distance and mode == 2) {
		mode = 3;
	}
	else if (distance(this, scary_target) > switch_distance and mode == 3) {
		mode = 2;
	}
}

void Snitch::Update() {

	switch_mode();

	// srand(Game::seed); //already done in Game.cpp?
	if (disappearing_mode == 1) {
		counter++;
		// int one = Game::FPS;

		if (counter ==  blinking_time) {
			vanish = 1;
			vanish_counter = 0;
			objTexture = vanish_texture;
		}

		else if (counter > blinking_time and counter < disapparation_time) {
			++vanish_counter;
			if (vanish_counter == vanish_time) {
				vanish_counter = 0;
				vanish = ! vanish ;
				if (vanish) {
					objTexture = vanish_texture;
				}
				else {
					objTexture = snitch_texture;
				}
			}
		}
		else if(counter == disapparation_time){
			// exists = false;
			// vanish = 1;
			// objTexture = vanish_texture;
		// }

		// else if(counter == apparation_time){

			counter = 0;
			vanish_counter = 0;
			vanish = 0;
			objTexture = snitch_texture;

			// set new position and velocity/path
			int starting_node = rand() % (Game::rows * Game::cols);
			set_starting_node(starting_node);
			if (mode == 2) {
				set_path_mode2();
			}
			else if (mode == 3) {
				set_path_mode3(scary_target);
			}

			// exists = true;

		}
	}

	Automated::Update();

}