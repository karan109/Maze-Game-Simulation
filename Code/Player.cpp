#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Player::Player(SDL_Rect srcR_param, int start) : Entity("../Images/pacman.png", srcR_param, start){
	showHealth = true;
	health = 30;
	if(showHealth){
		health_box = new Health(srcR_param, this);
		Game::entities->Add(health_box);
	}
}

void Player::Update(){
	int block_num = Entity::getBlock();
	set<int> obstacles;
	Entity::keepInside();
	auto coords = Entity::getCurrentBlockCoords();
	// if collision w wall then bring back to centre of path
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
	// if arrow key pressed
	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		// if no collision originally then change velocity
		if(key == SDLK_UP and obstacles.find(4) == obstacles.end()){
			// Game::send = 1;
			yv = -mag;
			xv = 0;
		}
		else if(key == SDLK_DOWN and obstacles.find(3) == obstacles.end()){
			// Game::send = 2;
			yv = mag;
			xv = 0;
		}
		else if(key == SDLK_RIGHT and obstacles.find(1) == obstacles.end()){
			// Game::send = 3;
			xv = mag;
			yv = 0;
		}
		else if(key == SDLK_LEFT and obstacles.find(2) == obstacles.end()){
			// Game::send = 4;
			xv = -mag;
			yv = 0;
		}
	}
	// if arrow key released
	if(Game::event.type == SDL_KEYUP){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP){
			// Game::send = -1;
			yv = 0;
		}
		else if(key == SDLK_DOWN){
			// Game::send = -2;
			yv = 0;
		}
		else if(key == SDLK_RIGHT){
			// Game::send = -3;
			xv = 0;
		}
		else if(key == SDLK_LEFT){
			// Game::send = -4;
			xv = 0;
		}
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
			if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 20)   // smooth turn
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