#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Entities.hpp"


int Monster::monster_i = 0;

void Monster::Delete() {
	Game::entities->Delete(health_box);
	Game::entities->Delete(static_health_box);
	Game::entities->Delete(this);

}
// number is needed for health
Monster::Monster(SDL_Rect srcR_param, int start, bool chase_start, int number_param) : Automated("../Images/dragon.png", srcR_param, start){

	original_mode = 0;
	original_speed = Game::monster_original_speed;
	speed = original_speed;
	target = nullptr;
	chase = chase_start;
	set_target();
	set_scary_target();
	number = number_param;
	monster_i++;
	monster_number = monster_i;

	showHealth = true;
	health = 100;
	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false, true);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}
}

Monster::Monster(SDL_Rect srcR_param, int start, int frames_param, int speed_param, bool chase_start, int number_param) : Automated("../Images/dragon.png", srcR_param, start){
	animated = true;
	srcR.y = srcR.h * 4;
	frames = frames_param;
	animate_speed = speed_param;
	
	original_mode = 0;
	original_speed = Game::monster_original_speed;
	speed = original_speed;
	chase = chase_start;
	target = nullptr;
	set_target();
	set_scary_target();
	number = number_param;
	monster_i++;
	monster_number = monster_i;

	dest = retreat_node; //retreat_node = start in Entity constructor

	showHealth = true;
	health = 100;
	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false, true);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}

}

void Monster::switch_in_scared_mode() {
	if (collided) return;


	if (scatter_reached == true and mode == 1) {
		bool mode_changed = change_mode(2);
		if (mode_changed)  {
			scatter_reached = false;
		}
	}

	if (scary_target == nullptr) return;
	if (distance(this, scary_target) <= 7 and mode == 2) {
		change_mode(3);
	}
	else if (distance(this, scary_target) > 15 and mode == 3) {
		change_mode(1);
	}

}

void Monster::switch_in_not_scared_mode() {

	if (collided) return;

	if(seq.empty()) {
		if (mode != 2) {
			change_mode(2);
		}
	}
	if (floor(normal_time) >= seq.front()) {
		if (mode == 0) {
			bool mode_changed = change_mode(2); 
			if (mode_changed) {
				seq.pop();
			}
		}
		else if (mode == 2) {
			bool mode_changed = change_mode(0); 
			if (mode_changed) {
				seq.pop();
			}
		}
	}

}
void Monster::determine_scared() {

	if (collided) return;

	if (spell_collision) {
		if (!spell_scared) {
			bool mode_changed = change_mode(3);
			if (mode_changed)  {
				spell_scared = true;
			}
		}
	}

	else if (!spell_collision) {
		if (spell_scared) {
			if (spell_collision_time >= 10) {
				reset_spell_collision_time();
				bool mode_changed = change_mode(0);
				if (mode_changed) spell_scared = false;
			}
		}

		// change to any player scary
		if (scary_target == nullptr) return;

		if (scary_target->scary == true) {

			if (!scared) {
				bool mode_changed = change_mode(3);
				if (mode_changed) scared = true;
			}
		}

		if (scary_target->scary == false) {	

			if (scared) {
				bool mode_changed = change_mode(0);//if target == nullptr change_mode(2)
				if (mode_changed) scared = false;
			}
		}

	}

}

void Monster::switch_modes() {

	if (collided) return;

	// scared || spellscared also can use insight
	if (scared) {		
		scared_time_update();
		switch_in_scared_mode();
	}
	else {
		normal_time_update();
		switch_in_not_scared_mode();
	}
}


void Monster::Update() {

	// Game::print_queue(seq);

	if(animated){
		srcR.x = srcR.w * ( (int) (SDL_GetTicks() / animate_speed) ) % frames;
	}

	if (collided) {
		Entity::Update();
		animated_stuff();
		if (spell_scared) {
			reset_spell_collision_time();
		}	
		return;
	}


	set_target();
	set_scary_target();

	if (spell_scared) {
		spell_collision_time_update();
	}

	Entity::Update();
	animated_stuff();
	handle_spell_collisions();
	// cout << "a"  << endl;
	determine_scared();
	// cout << "b"  << endl;
	switch_modes();
	// cout << "c"  << endl;
}



void Monster::normal_time_update() {
	normal_counter++;
	normal_time = (double) normal_counter / Game::FPS;
}
void Monster::scared_time_update() {
	scared_counter++;
	scared_time = (double) scared_counter / Game::FPS;
}


void Monster::set_target() {

	target = nearest_visible_player();
	if (target == nullptr) {
		// cout << "target nullptr" << endl;
		if (mode == 0) mode = 2;
	}

}

void Monster::set_scary_target() {

	scary_target = nearest_player();
	if (scary_target == nullptr) {
		// cout << "scary_target nullptr" << endl;
		if (mode == 1 || mode == 3) mode = 2;
		if (scared) scared = 0;
	}

}



void Monster::handle_spell_collisions() {
	spell_collision = 0;
	for(auto & spell: * Game::entities->spells){
		int dir = Collision::AABB(getBB(), spell->getBB(), getXV(), getYV(), spell->getXV(), spell->getYV());
		if (dir != 0) {
			// collided = 1;
			SDL_Rect R = this->getBB();
			// assert (dir == face)
			switch (spell->face) {
				case 1: spell->head = R.x; break;
				case 2: spell->head = R.x + R.w; break;
				case 3: spell->head = R.y; break;
				case 4: spell->head = R.y + R.h; break;
			}
			spell_collision = 1;

			decrease_health(0.5);
			spell->update_destR();

		}
	}
}


void Monster::spell_collision_time_update() {
	spell_collision_counter++;
	spell_collision_time = (double) spell_collision_counter / Game::FPS;
}
void Monster::reset_spell_collision_time() {
	spell_collision_counter = 0;
	spell_collision_time = 0;
}



void Monster::animated_stuff() {
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

}