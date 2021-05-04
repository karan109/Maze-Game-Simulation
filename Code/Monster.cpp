#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"


Monster::Monster(SDL_Rect srcR_param, int start) : Automated("../Images/dragon.png", srcR_param, start){
	speed = 2.5;
	target = nullptr;
}

Monster::Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param) : Automated("../Images/dragon.png", srcR_param, start){
	animated = true;
	srcR.y = srcR.h * 4;
	frames = frames_param;
	animate_speed = speed_param;
	speed = 2.5;
	target = nullptr;

	monster_retreat_node = Game::cols * Game::rows - 1; // change this for different monsters
	dest = monster_retreat_node;

	player_is_scary = 0;

	switch_distance_scared = 10;
	switch_distance_not_scared = 10;
}

void Monster::switch_in_scared_mode() {
	if (distance(this, scary_target) <= switch_distance_scared and mode == 2) {
		change_mode(3);
	}
	else if (distance(this, scary_target) > switch_distance_scared and mode == 3) {
		change_mode(1);
	}
	else if (scatter_reached = true and mode == 1) {
		change_mode(2);
	}
}

void Monster::switch_in_not_scared_mode() {
	if (distance(this, scary_target) <= switch_distance_not_scared and mode == 0) {
		change_mode(2);
	}
	else if (distance(this, scary_target) > switch_distance_not_scared and mode == 2) {
		change_mode(0);
	}
}


void Monster::Update() {
	if(animated){
		srcR.x = srcR.w * ( (int) (SDL_GetTicks() / animate_speed) ) % frames;
	}
	Automated::Update();
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

	if (player_is_scary == true) {
		if (mode == 0) {
			change_mode(3);
		}
		switch_in_scared_mode();
	}

	if (player_is_scary == false) {

		// cout <<" mode: " << mode << endl;
		
		if (mode != 0 || mode != 2) {
			change_mode(0);
		}
		// switch_in_not_scared_mode();
	}


}