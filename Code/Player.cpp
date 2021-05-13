#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Entities.hpp"

void Player::Delete() {
	SDL_DestroyTexture(objTexture);
	Game::entities->Delete(this);
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

	// health with time
	// if (fmod(entity_time, 0.5) == 0) {
	// 	if(health > 0) health-= 5;
	// } 

	update_boost();

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