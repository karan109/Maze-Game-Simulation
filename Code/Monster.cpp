#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"


Monster::Monster(SDL_Rect srcR_param, int start) : Automated("../Images/pacman.png", srcR_param, start){
	speed = 2.5;
	target = nullptr;
}

void Monster::Update(){
	if(target == nullptr) return;
	set_dest(target);
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
	int dir = Collision::AABB(getBB(), target->getBB(), getXV(), getYV(), target->getXV(), target->getYV());
	if(dir != 0){
		// if(dir == 1){
		// 	xpos = target->xpos - Game::player_w;
		// }
		// if(dir == 2){
		// 	xpos = target->xpos + Game::player_w;
		// }
		// if(dir == 3){
		// 	ypos = target->ypos - Game::player_h;
		// }
		// if(dir == 4){
		// 	ypos = target->ypos + Game::player_h;
		// }
		// destR.x = xpos;
		// destR.y = ypos;
		return;
	}
	auto coords = getAutoBlockCoords();
	int current = getBlock();
	int next = -1;
	if(!path.empty()){
		next = path.front();
		if(next == current){
			path.pop();
			next = path.front();
		}
	}
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;
	// int target_centre_x = target->xpos + Game::player_w / 2;
	// int target_centre_y = target->ypos + Game::player_h / 2;
	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){
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
void Monster::set_dest(Entity * target_param){
	while (!path.empty()){
		path.pop();
	}
	target = target_param;
	dest = target->getBlock();
	int init = Entity::getBlock();
	auto path_vector = Game::game_maze->graph.getPath(init, dest);
	for(auto vertex : path_vector){
		path.push(vertex);
	}
	current = path.front();
	path.pop();
}