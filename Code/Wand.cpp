#include "Game.hpp"
#include "Texture.hpp"
#include "Entities.hpp"
#include "Wand.hpp"

int Wand::num_wands = 0;
void Wand::Delete() {

	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);

}


Wand::Wand (SDL_Rect srcR_param, int start) : Entity("../Images/wand.png", srcR_param, start){
	num_wands++;
	wand_number = num_wands; // starting from 1
}
void Wand::Update() {

	handle_spell_collisions();
}

	