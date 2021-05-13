#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Entities.hpp"

void Monster::Delete() {
	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);
}

Monster::Monster(SDL_Rect srcR_param, int start) : Automated("../Images/dragon.png", srcR_param, start){

	original_mode = 0;
	original_speed = Game::monster_original_speed;
	speed = original_speed;
	target = nullptr;
}

Monster::Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param) : Automated("../Images/dragon.png", srcR_param, start){
	animated = true;
	srcR.y = srcR.h * 4;
	frames = frames_param;
	animate_speed = speed_param;
	
	original_mode = 0;
	original_speed = Game::monster_original_speed;
	speed = original_speed;

	target = nullptr;

	//Game::cols * Game::rows - 1; // change retreat node for different monsters
	dest = retreat_node; //retreat_node = start in Entity constructor

	// switch_distance_scared = 10;
	// switch_distance_not_scared = 10;
}

void Monster::switch_in_scared_mode() {
	if (distance(this, scary_target) <= 10 and mode == 2) {
		change_mode(3);
	}
	else if (distance(this, scary_target) > 20 and mode == 3) {
		change_mode(1);
	}
	else if (scatter_reached == true and mode == 1) {
		// scatter_reached = false;
		change_mode(2);
	}
}

void Monster::switch_in_not_scared_mode() {
	if (distance(this, scary_target) <= 5 and mode == 0) {
		change_mode(2);
	}
	else if (distance(this, scary_target) > 20 and mode == 2) {
		change_mode(0);
	}
}

void Monster::switch_modes() {
	if (collided) return;
	// change to any player scary
	if (target->scary == true) {

		if (!scared) {
			bool mode_changed = change_mode(3);
			if (mode_changed) scared = true;
		}
	}

	if (target->scary == false) {	

		if (scared) {
			bool mode_changed = change_mode(0);
			if (mode_changed) scared = false;
		}
	}

	// if (scared) switch_in_scared_mode();
	// else switch_in_not_scared_mode();
}


void Monster::Update() {

	// cout << mode << endl;
	
	if(animated){
		srcR.x = srcR.w * ( (int) (SDL_GetTicks() / animate_speed) ) % frames;
	}
	// collisions();
	Entity::Update();
	if(yv > 0){
		srcR.y = srcR.h * 2;
		face = 3;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(yv < 0){
		srcR.y = srcR.h * 0;
		face = 4;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(xv > 0){
		srcR.y = srcR.h * 1;
		face = 1;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(xv < 0){
		srcR.y = srcR.h * 3;
		face = 2;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else{
		// srcR.y = srcR.h * 4;
		// srcR.x = srcR.w * 7;
		animated = false;
	}

	if (!collided) switch_modes();

	// cout << mode << " " << scared << " " << scatter_reached << "path: [ "; print_path(); cout << " ]" << endl;
}