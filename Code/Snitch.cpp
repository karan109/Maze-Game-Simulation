#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Texture.hpp"
#include "Entities.hpp"

void Snitch::Delete() {
	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);
}

void Snitch::transform() {
	caught = 1;
	Entity::change_objTexture("../Images/Resurrection_Stone.png", SDL_Rect{0, 0, 549, 549}, destR);
	// set_pos_at_centre();
	set_velocity_zero();
}

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	
	original_speed = Game::snitch_original_speed;
	speed = original_speed;
	// scary_target = nullptr;
	original_mode = 2;
	set_mode(original_mode);
	vanish_texture = Texture::LoadTexture("../Images/empty.png");
	snitch_texture = Texture::LoadTexture("../Images/snitch.png");
	resurrection_stone_texture = Texture::LoadTexture("../Images/Resurrection_Stone.png");

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

	if (caught) {
		return;
	}

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

	Entity::Update();
	handle_spell_collisions();


}