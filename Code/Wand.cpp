#include "Game.hpp"
#include "Texture.hpp"
#include "Entities.hpp"
#include "Wand.hpp"

void Wand::Delete() {

	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);

}


Wand::Wand (SDL_Rect srcR_param, int start) : Entity("../Images/cute_wand.png", srcR_param, start){

}
void Wand::Update() {

	handle_spell_collisions();
}

