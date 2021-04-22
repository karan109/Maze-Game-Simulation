#include "Remote.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Remote::Remote(SDL_Rect srcR_param, int start) : Entity("../Images/pacman.png", srcR_param, start){
}

void Remote::Update(){
	int block_num = Entity::getBlock();
	set<int> obstacles;
	Entity::keepInside();
	auto coords = Entity::getCurrentBlockCoords();
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		obstacles.insert(dir);
		if(dir == 1){
			xv = 0;
			xpos = u->getBB().x - Game::block_w / 2 - destR.w / 2;
		}
		else if(dir == 2){
			xv = 0;
			xpos = u->getBB().x + u->getBB().w + Game::block_w / 2 - destR.w / 2;
		}
		else if(dir == 3){
			yv = 0;
			ypos = u->getBB().y - Game::block_h / 2 - destR.h / 2;
		}
		else if(dir == 4){
			yv = 0;
			ypos = u->getBB().y + u->getBB().h + Game::block_h / 2 - destR.h / 2;
		}
	}
	if(Game::response == 1 and obstacles.find(4) == obstacles.end()){
		yv = -mag;
		xv = 0;
	}
	else if(Game::response == 2 and obstacles.find(3) == obstacles.end()){
		yv = mag;
		xv = 0;
	}
	else if(Game::response == 3 and obstacles.find(1) == obstacles.end()){
		xv = mag;
		yv = 0;
	}
	else if(Game::response == 4 and obstacles.find(2) == obstacles.end()){
		xv = -mag;
		yv = 0;
	}
	if(Game::response == -1){
		yv = 0;
	}
	else if(Game::response == -2){
		yv = 0;
	}
	else if(Game::response == -3){
		xv = 0;
	}
	else if(Game::response == -4){
		xv = 0;
	}
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	coords = Entity::getCurrentBlockCoords();
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;
	if(yv == 0 and xv != 0){
		if( (xv == mag and Entity::getRight() != 1) or (xv == -mag and Entity::getLeft() != 1) ){
			if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 20)
				ypos = coords.first + Game::block_h / 2 - destR.h / 2;
		}
	}
	if(xv == 0 and yv != 0){
		if( (yv == mag and Entity::getDown() != 1) or (yv == -mag and Entity::getUp() != 1) ){
			if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 20)
				xpos = coords.second + Game::block_w / 2 - destR.w / 2;
		}
	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}