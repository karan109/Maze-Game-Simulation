#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Player::Player(SDL_Rect srcR_param, SDL_Rect destR_param) : Entity("../Images/man.png", srcR_param, destR_param){
}

void Player::Update(){
	int block_num = Entity::getBlock();
	set<int> obstacles;
	Entity::keepInside();
	auto coords = Entity::getCurrentBlockCoords();
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		obstacles.insert(dir);
		if(dir == 1){
			xv = 0;
			xpos = u->getBB().x - block_w / 2 - destR.w / 2;
			// ypos = coords.first + block_h / 2 - destR.h / 2;
		}
		else if(dir == 2){
			xv = 0;
			xpos = u->getBB().x + u->getBB().w + block_w / 2 - destR.w / 2;
			// ypos = coords.first + block_h / 2 - destR.h / 2;
		}
		else if(dir == 3){
			yv = 0;
			ypos = u->getBB().y - block_h / 2 - destR.h / 2;
			xpos = coords.second + block_w / 2 - destR.w / 2;
		}
		else if(dir == 4){
			yv = 0;
			ypos = u->getBB().y + u->getBB().h + block_h / 2 - destR.h / 2;
			// xpos = coords.second + block_w / 2 - destR.w / 2;
		}
	}
	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP and obstacles.find(4) == obstacles.end()){
			yv = -1;
			xv = 0;
		}
		else if(key == SDLK_DOWN and obstacles.find(3) == obstacles.end()){
			yv = 1;
			xv = 0;
		}
		else if(key == SDLK_RIGHT and obstacles.find(1) == obstacles.end()){
			xv = 1;
			yv = 0;
		}
		else if(key == SDLK_LEFT and obstacles.find(2) == obstacles.end()){
			xv = -1;
			yv = 0;
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
	int row = block_num / cols;
	int col = block_num % cols;
	coords = Entity::getCurrentBlockCoords();
	if(yv == 0 and xv != 0){
		if( (xv == 1 and Entity::getRight() != 1) or (xv == -1 and Entity::getLeft() != 1) ){
			ypos = coords.first + block_h / 2 - destR.h / 2;
		}
	}
	if(xv == 0 and yv != 0){
		if( (yv == 1 and Entity::getDown() != 1) or (yv == -1 and Entity::getUp() != 1) ){
			xpos = coords.second + block_w / 2 - destR.w / 2;
		}
	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}