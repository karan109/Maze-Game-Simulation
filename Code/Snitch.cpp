#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Texture.hpp"

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	speed = 2.5;
	set_mode(2);
	vanish_texture = Texture::LoadTexture("../Images/water.png");
	snitch_texture = Texture::LoadTexture("../Images/snitch.png");

	vanish_counter = 0;
	vanish = 0;
	
	blinking_time = Game::FPS * 8;
	disapparation_time = Game::FPS * 10;
	apparation_time = Game::FPS * 11;
	vanish_time = Game::FPS * 0.1;


}

void Snitch::Update() {

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
			set_path_mode2(0);

			// exists = true;

		}
	}

	Automated::Update();

}