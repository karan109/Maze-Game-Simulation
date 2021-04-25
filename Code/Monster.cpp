#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"


Monster::Monster(SDL_Rect srcR_param, int start) : Automated("../Images/pacman.png", srcR_param, start){
	speed = 2.5;
	target = nullptr;
}

void Monster::Update(){

	if (mode == 0) {

		if(target == nullptr) return;
		// changes path as target moves 
		Automated::set_dest(target);

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
		// if collides with target then return
		int dir = Collision::AABB(getBB(), target->getBB(), getXV(), getYV(), target->getXV(), target->getYV());
		if(dir != 0){
			// xv = 0;	no cleanup
			return;
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
					return;
				}
			}
		}
		int centre_x = xpos + destR.w / 2;
		int centre_y = ypos + destR.h / 2;
		int block_centre_y = coords.first + Game::block_h / 2;
		int block_centre_x = coords.second + Game::block_w / 2;
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



	if (mode == 2) {
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
}























// void Monster::set_dest(Entity * target_param){
// 	while (!path.empty()){
// 		path.pop();
// 	}
// 	target = target_param;
// 	dest = target->getBlock();
// 	int init = Entity::getBlock();
// 	auto path_vector = Game::game_maze->graph.getPath(init, dest);
// 	for(auto vertex : path_vector){
// 		path.push(vertex);
// 	}
// 	current = path.front();
// 	path.pop();
// }


	// if (mode == 2) {
	
	// 	Entity::keepInside();	
	// 	srand(time(0));
		
	// 	for(auto & u: * Game::entities->walls){
	// 		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
	// 		if(dir == 1){
	// 			xv = 0;
	// 			xpos -= mag * speed;
	// 			return;
	// 		}
	// 		else if(dir == 2){
	// 			xv = 0;
	// 			xpos += mag * speed;
	// 			return;
	// 		}
	// 		else if(dir == 3){
	// 			yv = 0;
	// 			ypos -= mag * speed;
	// 			return;
	// 		}
	// 		else if(dir == 4){
	// 			yv = 0;
	// 			ypos += mag * speed;
	// 			return;
	// 		}
	// 	}

	// 	int block_num = getBlock();
	// 	// auto coords = Entity::getAutoBlockCoords(); 
	// 	auto coords = Entity::getCurrentBlockCoords();
		
	// 	int centre_x = xpos + destR.w / 2;
	// 	int centre_y = ypos + destR.h / 2;
	// 	int block_centre_y = coords.first + Game::block_h / 2;
	// 	int block_centre_x = coords.second + Game::block_w / 2;


	// 	if (xv == 0 and yv == 0) {
	// 		vector<int> v;
	// 		if (Entity::getRight() != 1) v.push_back(0);
	// 		if (Entity::getDown() != 1) v.push_back(1);
	// 		if (Entity::getLeft() != 1) v.push_back(2);
	// 		if (Entity::getUp() != 1) v.push_back(3);
	// 		int temp = rand() % v.size();
	// 		if (v[temp] == 0) xv = mag;
	// 		if (v[temp] == 1) yv = mag;
	// 		if (v[temp] == 2) xv = -mag;
	// 		if (v[temp] == 3) yv = -mag;
	// 	}

		
	// 	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){

	// 		if(yv == 0 and xv != 0){

	// 			bool up = ! Entity::getUp();
	// 			bool down = ! Entity::getDown();

	// 			// go up
	// 			if ( (up == 1 and down == 0 and rand() % 2 == 1) || (up == 1 and down == 1 and rand() % 3 == 1) ) {
	// 				ypos = coords.first + Game::block_h / 2 - destR.h / 2;
	// 				yv = -mag;
	// 				xv = 0;
	// 			}

	// 			// go down
	// 			if ( (down == 1 and up == 0 and rand() % 2 == 1) || (down == 1 and up == 1 and rand() % 3 == 2) ) {
	// 				ypos = coords.first + Game::block_h / 2 - destR.h / 2;
	// 				yv = mag;
	// 				xv = 0;
	// 			}
	// 		}


	// 		if(xv == 0 and yv != 0){

	// 			bool left = ! Entity::getLeft();
	// 			bool right = ! Entity::getRight();

	// 			// go left
	// 			if ( (left == 1 and right == 0 and rand() % 2 == 1) || (left == 1 and right == 1 and rand() % 3 == 1) ) {
	// 				xpos = coords.second + Game::block_h / 2 - destR.h / 2;
	// 				xv = -mag;
	// 				yv = 0;
	// 			}

	// 			// go right
	// 			if ( (right == 1 and left == 0 and rand() % 2 == 1) || (right == 1 and left == 1 and rand() % 3 == 2) ) {
	// 				xpos = coords.second + Game::block_h / 2 - destR.h / 2;
	// 				xv = mag;
	// 				yv = 0;
	// 			}
	// 		}
	// 	}

	// 	xpos += xv * speed;
	// 	ypos += yv * speed;
		
	// 	destR.x = xpos;
	// 	destR.y = ypos;

	// }
