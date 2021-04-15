#include "Player.hpp"
#include "Game.hpp"
#include "Entities.hpp"
#include "Collision.hpp"

Player::Player(SDL_Rect srcR_param, SDL_Rect destR_param) : Entity("../Images/man.png", srcR_param, destR_param){
}

void Player::Update(){
	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP){
			yv = -1;
		}
		else if(key == SDLK_DOWN){
			yv = 1;
		}
		else if(key == SDLK_RIGHT){
			xv = 1;
		}
		else if(key == SDLK_LEFT){
			xv = -1;
		}
	}
	if(Game::event.type == SDL_KEYUP){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP){
			yv = 0;
		}
		else if(key == SDLK_DOWN){
			yv = 0;
		}
		else if(key == SDLK_RIGHT){
			xv = 0;
		}
		else if(key == SDLK_LEFT){
			xv = 0;
		}
	}
	for(auto & u: *entities->walls){
		if(Collision::AABB(getBB(), u->getBB())){
			// xv = 0;
			// yv = 0;
			break;
		}
	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}