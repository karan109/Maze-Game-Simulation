#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Player::Player(SDL_Rect srcR_param, SDL_Rect destR_param) : Entity("../Images/man.png", srcR_param, destR_param){
}

void Player::Update(){
	set<int> obstacles;
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB());
		obstacles.insert(dir);
		if(dir == 1 or dir == 2){
			xv = 0;
		}
		if(dir == 3 or dir == 4){
			yv = 0;
		}
	}
	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP and obstacles.find(4) == obstacles.end()){
			yv = -1;
		}
		else if(key == SDLK_DOWN and obstacles.find(3) == obstacles.end()){
			yv = 1;
		}
		else if(key == SDLK_RIGHT and obstacles.find(1) == obstacles.end()){
			xv = 1;
		}
		else if(key == SDLK_LEFT and obstacles.find(2) == obstacles.end()){
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
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}