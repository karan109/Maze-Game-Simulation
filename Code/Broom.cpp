#include "Game.hpp"
#include "Collision.hpp"
#include "Texture.hpp"
#include "Entities.hpp"
#include "Broom.hpp"


void Broom::Delete() {

	counter = 0;
	vanish_counter = 0;
	vanish = 0;
	objTexture = vanish_texture;

	exists = 0;

	// if (caught) {

	// 	my_player->scary = 0;
	// 	my_player->boost = 0;
	// 	my_player->speed = my_player->original_speed;

	// 	my_player->my_broom = nullptr;
	// 	caught = 0;
	// 	my_player = nullptr;

	// }
	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);

}


Broom::Broom (SDL_Rect srcR_param, int start) : Entity("../Images/broom.png", srcR_param, start){

	broom_texture = Texture::LoadTexture("../Images/broom.png");
	vanish_texture = Texture::LoadTexture("../Images/empty.png");


	vanish_counter = 0;
	vanish = 0;
	
	disapparation_time = Game::FPS * Game::broom_disapparation_time;
	blinking_time = disapparation_time - 2 * Game::FPS;
	// apparation_time = Game::FPS * 11;
	vanish_time = Game::FPS * 0.2;
	exists = 1;

}
void Broom::Update() {

	// srand(Game::seed); //already done in Game.cpp?

	// if (caught) then get attached to player
	
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
				objTexture = broom_texture;
			}
		}
	}
	else if(counter == disapparation_time){
		// delete the broom
		Game::display_message("broom disapparated");
		Delete();
	}

	handle_spell_collisions();

}

