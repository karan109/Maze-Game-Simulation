#include "Spell.hpp"
#include "Game.hpp"
#include "Collision.hpp"



// ------------------------------------------------------constructors--------------------------------------------------------------------------------------

void Spell::Delete() {
	// if (objTexture != nullptr) SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);
}

Spell::Spell(Player * castee) {
	wizard = castee;
	original_face = wizard->face;
	face = original_face;
	speed = 6;
	offset = 0;
	spell_height = 5;
	tail = get_tail();
	head = tail;
	length = 0;
	set_velocity();
	initialize_head_tail_velocity();	
	destR = set_rect();
	released = 0;
	spell_length_limit = 200;

}
void Spell::set_velocity() {
	pair<int, int> v = get_dir();
	xv = v.first;
	yv = v.second;
}

void Spell::initialize_head_tail_velocity() {
	if (face == 1 || face == 2) {
		head_v = xv;
	}
	else head_v = yv;
	tail_v = head_v;
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
	// face used instead of original_face
	if (wizard->face != face) {
		return 1;
	}
	// if spell casting ability becomes 0 or health becomes 0
	// if player collision happens
	// if player spelling limit reached ie wand exhausted. get a new wand
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

	if (release_conditions() ) {
		if (!released) release_spell();
	}

	if (!collided) {
		handle_wall_collision();
	}

	if (collided) {
		handle_spell_over();
	}

	// if (finished) {
	// 	Delete();
	// }



}

void Spell::update_head() {
	head += head_v * speed;
}
void Spell::update_tail() {
	if (released) {
		tail += tail_v * speed;
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


// ------------------------------------------------------collisions--------------------------------------------------------------------------------------


void Spell::handle_spell_over() {
	if (spell_over()) {
		collided = 0;
		finished = 1;
		// set_tail_velocity_0
		//in next cycle. can cause errors if done in this loop?
		Delete(); 
	}
}

bool Spell::spell_over() {
	if (face == 1 || face == 3) {
		if (tail >= head) {
			return 1;
		}
		return 0;
	}
	else {
		if (tail <= head) {
			return 1;
		}
		return 0;
	}
}

void Spell::handle_wall_collision() {
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		if (dir != 0) {
			collided = 1;
			// assert (dir == face)
			head_v = 0;
		}
	}
}



// ------------------------------------------------------render--------------------------------------------------------------------------------------



void Spell::Render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(Game::renderer, &destR);
}

