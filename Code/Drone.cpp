#include "Drone.hpp"
#include "Game.hpp"
#include "Collision.hpp"


Drone::Drone(SDL_Rect srcR_param, int start) : Automated("../Images/pacman.png", srcR_param, start){
	speed = 4;
}

void Drone::Update(){
	if(path.empty()) return;
	Entity::keepInside();
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		if(dir == 1){
			xv = 0;
			xpos -= mag * speed;
			return;
		}
		else if(dir == 2){
			xv = 0;
			xpos += mag * speed;
			return;
		}
		else if(dir == 3){
			yv = 0;
			ypos -= mag * speed;
			return;
		}
		else if(dir == 4){
			yv = 0;
			ypos += mag * speed;
			return;
		}
	}
	auto coords = getAutoBlockCoords();
	int current = getBlock();
	int next = path.front();
	if(next == current){
		path.pop();
		next = path.front();
	}
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;
	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){
		if(path.empty()){
			xv = 0;
			yv = 0;
			coords = getAutoBlockCoords();
			ypos = coords.first + Game::block_h / 2 - destR.h / 2;
			xpos = coords.second + Game::block_w / 2 - destR.w / 2;
			return;
		}
		if(next == current + 1){
			xv = mag;
			yv = 0;
			ypos = coords.first + Game::block_h / 2 - destR.h / 2;
		}
		else if(next == current - 1){
			xv = -mag;
			yv = 0;
			ypos = coords.first + Game::block_h / 2 - destR.h / 2;
		}
		else if(next == current + Game::cols){
			xv = 0;
			yv = mag;
			xpos = coords.second + Game::block_w / 2 - destR.w / 2;
		}
		else if(next == current - Game::cols){
			xv = 0;
			yv = -mag;
			xpos = coords.second + Game::block_w / 2 - destR.w / 2;
		}

	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}