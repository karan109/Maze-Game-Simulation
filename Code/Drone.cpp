#include "Drone.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Drone::Drone(SDL_Rect srcR_param, SDL_Rect destR_param, int dest) : Entity("../Images/man.png", srcR_param, destR_param){
	int init = Entity::getBlock();
	auto path_vector = Game::game_maze->graph.getPath(init, dest);
	for(auto vertex : path_vector){
		path.push(vertex);
	}
	current = path.front();
	path.pop();
}

void Drone::Update(){
	int speed = 2;
	int block_num = Entity::getBlock();
	current = block_num;
	int next = path.front();
	auto coords = getAutoBlockCoords();

	set<int> obstacles;
	Entity::keepInside();
	// cout<<current<<endl;
	// print_path();
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		obstacles.insert(dir);
		if(dir == 1){
			xv = 0;
			xpos = u->getBB().x - block_w / 2 - destR.w / 2;
			ypos = coords.first + block_h / 2 - destR.h / 2;
		}
		else if(dir == 2){
			xv = 0;
			xpos = u->getBB().x + u->getBB().w + block_w / 2 - destR.w / 2;
			ypos = coords.first + block_h / 2 - destR.h / 2;
		}
		else if(dir == 3){
			yv = 0;
			ypos = u->getBB().y - block_h / 2 - destR.h / 2;
			xpos = coords.second + block_w / 2 - destR.w / 2;
		}
		else if(dir == 4){
			yv = 0;
			ypos = u->getBB().y + u->getBB().h + block_h / 2 - destR.h / 2;
			xpos = coords.second + block_w / 2 - destR.w / 2;
		}
	}
	coords = getAutoBlockCoords();
	current = getBlock();
	if(next == current){
		path.pop();
		next = path.front();
	}
	if(next == current + 1){
		xv = 1;
		yv = 0;
		ypos = coords.first + block_h / 2 - destR.h / 2;
	}
	else if(next == current - 1){
		xv = -1;
		yv = 0;
		ypos = coords.first + block_h / 2 - destR.h / 2;
	}
	else if(next == current + cols){
		xv = 0;
		yv = 1;
		xpos = coords.second + block_w / 2 - destR.w / 2;
	}
	else if(next == current - cols){
		xv = 0;
		yv = -1;
		xpos = coords.second + block_w / 2 - destR.w / 2;
	}
	int row = block_num / cols;
	int col = block_num % cols;
	coords = getAutoBlockCoords();
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
pair<int, int> Drone::getAutoBlockCoords(){
	int block_num = getBlock();
	int row = block_num / cols;
	int col = block_num % cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(mtr_row % 2 == 0 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (block_h + wall_thickness), (mtr_col / 2) * (block_w + wall_thickness) };
	}
	else if(mtr_row % 2 == 1 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (block_h + wall_thickness) + block_h, (mtr_col / 2) * (block_w + wall_thickness) };
	}
	else if(mtr_row % 2 == 0 and mtr_col % 2 == 1){
		return { (mtr_row / 2) * (block_h + wall_thickness), (mtr_col / 2) * (block_w + wall_thickness) + block_w };
	}
	else return { (mtr_row / 2) * (block_h + wall_thickness) + block_h, (mtr_col / 2) * (block_w + wall_thickness) + block_w };
}