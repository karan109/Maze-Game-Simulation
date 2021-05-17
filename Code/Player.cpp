#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Entities.hpp"
#include "Spell.hpp"


void Player::Delete() {
	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(health_box);
	Game::entities->Delete(static_health_box);
	Game::entities->Delete(this);
	// what if this is the target of something?
}

Player::Player(SDL_Rect srcR_param, int start, int number_param) : Entity("../Images/pacman.png", srcR_param, start){

	original_speed = Game::player_original_speed;
	speed = original_speed;
	boost_speed = Game::player_boost_speed;
	boost_time_limit = Game::player_boost_time_limit;
	original_mode = -1;
	set_mode(original_mode); //mode = -1;
	dest = retreat_node;
	boost_time_left = 0;



	showHealth = true;
	health = 100;
	health_dps = Game::player_health_decrement_per_second;
	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}
}

Player::Player(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param) : Entity(("../Images/"+Game::player_name+".png").c_str(), srcR_param, start){
	
	original_speed = Game::player_original_speed;
	speed = original_speed;
	boost_speed = Game::player_boost_speed;
	boost_time_limit = Game::player_boost_time_limit;
	original_mode = -1;
	set_mode(original_mode); //mode = -1;
	dest = retreat_node;
	boost_time_left = 0;


	animated = true;
	srcR.y = srcR.h * 4;
	frames = frames_param;
	animate_speed = speed_param;
	showHealth = true;
	health = 100;
	health_dps = Game::player_health_decrement_per_second;

	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}
}


void Player::Update(){

	// cout << xpos << " " << destR.x << " " << ypos << " " <<destR.y << endl;

	// time_update();


	update_boost();

	if (casting_conditions() ) {
		// cout << 1 << endl;
		cast_spell();
	}

	if(animated){
		srcR.x = srcR.w * ( (int) (SDL_GetTicks() / animate_speed) ) % frames;
	}
	

	Entity::Update();

	
	// face = 1 right facing
	// face = 2 left facing
	// face = 3 down facing
	// face = 4 up facing
	if(yv > 0){
		srcR.y = srcR.h * 4;
		face = 3;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(yv < 0){
		srcR.y = srcR.h * 7;
		face = 4;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(xv > 0){
		srcR.y = srcR.h * 6;
		face = 1;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else if(xv < 0){
		srcR.y = srcR.h * 5;
		face = 2;
		if(! animated) srcR.x = 0;
		animated = true;
	}
	else{
		// srcR.y = srcR.h * 4;
		// srcR.x = srcR.w * 7;
		animated = false;
	}

	handle_spell_collisions();


	// health with time
	if (!snitch_caught) {
		if (fmod(entity_time, 1.0) == 0) {
			decrease_health(health_dps);
		}
	}
	// cout << health << endl;
	// if (health == 0) {
	// 	Delete();
	// }

	handle_spell_collisions();



}


void Player::boost_on() {
	scary = 1;
	boost = 1;
	speed = boost_speed;
	boost_time_left = boost_time_limit; // is reset to max val when 2nd boost even if first not over
}


void Player::boost_off() {
	scary = 0;
	boost = 0;
	speed = original_speed;
	boost_time_left = 0;
	// Game::game_pause(1);
}



void Player::update_boost_time_left() {
	// display only ceil(boost_time_left)
	boost_time_left -= (double) 1 / Game::FPS;
	// cout << boost_time_left << endl;
}

void Player::update_boost() {
	if (!boost) return;
	// display_boost();
	update_boost_time_left();
	if (boost_time_left <= 0) {
		boost_off();
	}

}


bool Player::casting_conditions() {
	// if wand is not caught
	// if (!wanded) return;
	// cout << " player casting condition used";


	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_SPACE)  {
			if (Game::spacebar_pressed == 0) {
				// Game::spacebar_pressed = 1;
				return 1;
			}
		}
	}

	return 0;	
}



void Player::cast_spell() {
	Spell * spell = new Spell(this);
	Game::entities->Add(spell);
	// add spell to entities
}


void Player::handle_spell_collisions() {
	spell_collision = 0;
	for(auto & spell: * Game::entities->spells){
		int dir = Collision::AABB(getBB(), spell->getBB(), getXV(), getYV());
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
		}
	}
}








