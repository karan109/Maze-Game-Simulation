#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Player::Player(SDL_Rect srcR_param, SDL_Rect destR_param) : Entity("../Images/man.png", srcR_param, destR_param){
}

void Player::Update(){
	int block_num = getBlock();
	set<int> obstacles;
	for(auto & u: * Game::entities->walls){
		int dir = Collision::AABB(getBB(), u->getBB(), getXV(), getYV());
		obstacles.insert(dir);
		if(dir == 1){
			xv = 0;
			xpos = u->getBB().x - destR.w;
		}
		if(dir == 2){
			xv = 0;
			xpos = u->getBB().x + u->getBB().w;
		}
		if(dir == 3){
			yv = 0;
			ypos = u->getBB().y - destR.h;
		}
		if(dir == 4){
			yv = 0;
			ypos = u->getBB().y + u->getBB().h;
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
	if(yv == 0 and xv != 0){
		if( (xv == 1 and getRight() != 1) or (xv == -1 and getLeft() != 1) ){
			ypos = row * (block_h + wall_thickness) + block_h / 2 - destR.h / 2;
		}
	}
	if(xv == 0 and yv != 0){
		if( (yv == 1 and getDown() != 1) or (yv == -1 and getUp() != 1) )
			xpos = col * (block_w + wall_thickness) + block_w / 2 - destR.w / 2;
	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
}
int Player::getBlock(){
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int row = centre_y / (block_h + wall_thickness);
	int col = centre_x / (block_w + wall_thickness);
	return row * cols + col;
}
bool Player::getRight(){
	int block_num = getBlock();
	int row = block_num / cols;
	int col = block_num % cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (block_h + wall_thickness) + block_h) ) mtr_row++;
	if(centre_x >= (col * (block_w + wall_thickness) + block_h) ) mtr_col++;
	if(mtr_col + 1 < cols * 2) return game_Maze[mtr_row][mtr_col + 1];
	else return 0;
}
bool Player::getLeft(){
	int block_num = getBlock();
	int row = block_num / cols;
	int col = block_num % cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (block_h + wall_thickness) + block_h) ) mtr_row++;
	if(centre_x >= (col * (block_w + wall_thickness) + block_h) ) mtr_col++;
	if(mtr_col - 1 >= 0) return game_Maze[mtr_row][mtr_col - 1];
	else return 0;
}
bool Player::getUp(){
	int block_num = getBlock();
	int row = block_num / cols;
	int col = block_num % cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (block_h + wall_thickness) + block_w) ) mtr_row++;
	if(centre_x >= (col * (block_w + wall_thickness) + block_w) ) mtr_col++;
	if(mtr_row - 1 >= 0) return game_Maze[mtr_row - 1][mtr_col];
	else return 0;
}
bool Player::getDown(){
	int block_num = getBlock();
	int row = block_num / cols;
	int col = block_num % cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (block_h + wall_thickness) + block_w) ) mtr_row++;
	if(centre_x >= (col * (block_w + wall_thickness) + block_w) ) mtr_col++;
	if(mtr_row + 1 >= rows * 2) return game_Maze[mtr_row + 1][mtr_col];
	else return 0;
}