#include "Spell.hpp"
#include "Game.hpp"


// ------------------------------------------------------constructors--------------------------------------------------------------------------------------


Spell::Spell(Player * castee) {
	wizard = castee;
	face = wizard->face;
	speed = 6;
	offset = 0;
	spell_height = 5;
	tail = get_tail();
	head = tail;
	length = 0;
	set_velocity();
	destR = set_rect();
	released = 0;
	spell_length_limit = 200;

}
void Spell::set_velocity() {
	pair<int, int> v = get_dir();
	xv = v.first;
	yv = v.second;
}

SDL_Rect Spell::set_rect() {
	
	SDL_Rect DestR = wizard->destR;

	switch (face) {

		case 1: return SDL_Rect{DestR.x + DestR.w + offset, DestR.y + DestR.h / 2 - spell_height/2, 0 , spell_height};
		case 2: return SDL_Rect{DestR.x - offset - length , DestR.y + DestR.h / 2 - spell_height/2, 0 , spell_height};
		case 3: return SDL_Rect{DestR.x + DestR.w/2 - spell_height / 2, DestR.y + DestR.h + offset, spell_height, 0}; 
		case 4: return SDL_Rect{DestR.x + DestR.w / 2 - spell_height/2, DestR.y - offset - length, spell_height, 0};
		
	}
}

// ------------------------------------------------------player related auxilaries--------------------------------------------------------------------------------------

// spell centre starting point
pair <int, int> Spell::getfacepoint() {
	SDL_Rect DestR = wizard->destR;
	switch (face) {

		case 1: return {DestR.x + DestR.w + offset, DestR.y + DestR.h / 2};
		case 2: return {DestR.x - offset , DestR.y + DestR.h / 2};
		case 3: return {DestR.x + DestR.w/2, DestR.y + DestR.h + offset}; 
		case 4: return {DestR.x + DestR.w / 2, DestR.y - offset};
		
	}
}
// spell velocity direction
pair <int, int> Spell::get_dir() {
	switch (face) {
		case 1: return {1,0};
		case 2: return {-1,0};
		case 3: return {0,1}; 
		case 4: return {0,-1};		
	}
}

int Spell::get_tail(){
	SDL_Rect DestR = wizard->destR;

	switch (face) {

		case 1: return DestR.x + DestR.w + offset;
		case 2: return DestR.x - offset;
		case 3: return DestR.y + DestR.h + offset; 
		case 4: return DestR.y - offset;
		
	}
}

bool Spell::release_conditions() {
	// if already released??
	// ie casting/pressed = 0
	// cout << "idk wtf" << endl;
	if(Game::event.type == SDL_KEYUP){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_SPACE)  {
			if (Game::spacebar_pressed == 1) {
				// Game::spacebar_pressed = 0;
				return 1;
			}
		}
	}
	if (length >= spell_length_limit) return 1;
	// if direction of player changed
	// if spell casting ability becomes 0 or health becomes 0
	// if player collision happens
	// if player spell time limit reached.
	return 0;
}



// ------------------------------------------------------updates--------------------------------------------------------------------------------------


void Spell::Update() {
	// handle wall collision
	// time update
	update_head();
	update_tail();
	length = abs(head - tail);
	destR = get_rect();

		// in spell
	if (release_conditions() ) {
		if (!released) release_spell();
	}

}

void Spell::update_head() {
	// one of xv, yv = 0
	head += (xv + yv) * speed;
}
void Spell::update_tail() {
	if (released) {
		tail += (xv + yv) * speed;
	}

	// else if still casting then follow player
	else tail = get_tail();

}

SDL_Rect Spell::get_rect() {
	switch (face) {
		case 1: return SDL_Rect{tail, destR.y, length, spell_height};
		case 2: return SDL_Rect{head , destR.y, length, spell_height};
		case 3: return SDL_Rect{destR.x, tail , spell_height, length}; 
		case 4: return SDL_Rect{destR.x, head , spell_height, length};
	}
}

void Spell::release_spell(){
	released = 1;
}



// ------------------------------------------------------render--------------------------------------------------------------------------------------



void Spell::Render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(Game::renderer, &destR);
}


