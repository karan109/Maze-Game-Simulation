#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	speed = 2.5;
}

 

void Snitch::Update() {
	Entity::keepInside();
	srand(time(0));

	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		if(dir == 1){
			xv = 0;
			xpos -= mag * speed;		// different from player
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

	int next = INT_MIN;
	if(!path.empty()){
		next = path.front();
		if(next == current){
			path.pop();
			if (!path.empty()) {
				next = path.front();
			}
			else {
				next = INT_MIN;
			}
		}
	}

	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;

	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){
		if(path.empty()){
			// cout<<"hi"<<endl;
			vector <int> temp;


			if (xv == mag and yv == 0) {
				if (Entity::can_go_right(current)) temp.push_back(0);
				if (Entity::can_go_down(current)) temp.push_back(1);
				// if (Entity::can_go_left(current)) temp.push_back(2);
				if (Entity::can_go_up(current)) temp.push_back(3);
			}

			if (xv == -mag and yv == 0) {
				// if (Entity::can_go_right(current)) temp.push_back(0);
				if (Entity::can_go_down(current)) temp.push_back(1);
				if (Entity::can_go_left(current)) temp.push_back(2);
				if (Entity::can_go_up(current)) temp.push_back(3);
			}

			if (yv == mag and xv == 0) {
				if (Entity::can_go_right(current)) temp.push_back(0);
				if (Entity::can_go_down(current)) temp.push_back(1);
				if (Entity::can_go_left(current)) temp.push_back(2);
				// if (Entity::can_go_up(current)) temp.push_back(3);
			}

			if (yv == -mag and xv == 0) {
				if (Entity::can_go_right(current)) temp.push_back(0);
				// if (Entity::can_go_down(current)) temp.push_back(1);
				if (Entity::can_go_left(current)) temp.push_back(2);
				if (Entity::can_go_up(current)) temp.push_back(3);
			}

			if (xv == 0 and yv == 0) {
				if (Entity::can_go_right(current)) temp.push_back(0);
				if (Entity::can_go_down(current)) temp.push_back(1);
				if (Entity::can_go_left(current)) temp.push_back(2);
				if (Entity::can_go_up(current)) temp.push_back(3);
			}

			// assert(temp.size()!=0);

			int temp_dir = temp[rand() % temp.size()];
			xv = 0;
			yv = 0;
			if (temp_dir == 0) {
				next = current + 1;
				xv = mag; 
			} 
			if (temp_dir == 1) {
				next = current + Game::cols;
				yv = mag; 
			}
			if (temp_dir == 2) {
				next = current - 1;
				xv = -mag; 
			}
			if (temp_dir == 3) {
				next = current - Game::cols;
				yv = -mag; 
			}
			path.push(next);



			coords = getAutoBlockCoords();
			ypos = coords.first + Game::block_h / 2 - destR.h / 2;
			xpos = coords.second + Game::block_w / 2 - destR.w / 2;
			destR.x = xpos;
			destR.y = ypos;

			return;
		}
		else if(next == current + 1){
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
