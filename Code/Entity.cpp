#include "Game.hpp"
#include "Entity.hpp"
#include "Texture.hpp"

Entity::Entity(const char * texturesheet, SDL_Rect srcR_param, int start){
	objTexture = Texture::LoadTexture(texturesheet);
	auto coords = getAutoBlockCoords(start);
	destR.x = coords.second + Game::block_w / 2 - Game::player_w / 2;
	destR.y = coords.first + Game::block_h / 2 - Game::player_h / 2;
	destR.w = Game::player_w;
	destR.h = Game::player_h;
	srcR = srcR_param;
	xpos = destR.x;
	ypos = destR.y;
	xv = 0;
	yv = 0;
}
Entity::Entity(const char * texturesheet, SDL_Rect srcR_param, SDL_Rect destR_param){
	objTexture = Texture::LoadTexture(texturesheet);
	srcR = srcR_param;
	destR = destR_param;
	xpos = destR.x;
	ypos = destR.y;
	xv = 0;
	yv = 0;
}
void Entity::Update(){
	
}
void Entity::Render(){
	SDL_RenderCopy(Game::renderer, objTexture, & srcR, & destR);
}
Entity::~Entity(){
	SDL_DestroyTexture(objTexture);
}
int Entity::getX(){
	return xpos;
}
int Entity::getY(){
	return ypos;
}
void Entity::setX(int x){
	xpos = x;
}
void Entity::setY(int y){
	ypos = y;
}
int Entity::getXV(){
	return xv;
}
int Entity::getYV(){
	return yv;
}
void Entity::setXV(int xv_param){
	xv = xv_param;
}
void Entity::setYV(int yv_param){
	yv = yv_param;
}
SDL_Rect Entity::getBB(){
	return destR;
}
int Entity::getBlock(){
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int row = centre_y / (Game::block_h + Game::wall_thickness);
	int col = centre_x / (Game::block_w + Game::wall_thickness);
	return row * Game::cols + col;
}
pair<int, int> Entity::getCurrentBlockCoords(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_row % 2 == 0 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 1 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 0 and mtr_col % 2 == 1){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
	}
	else return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
}
bool Entity::getRight(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_col + 1 < Game::cols * 2) return game_Maze[mtr_row][mtr_col + 1];
	else return 1;
}
bool Entity::getLeft(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_col - 1 >= 0) return game_Maze[mtr_row][mtr_col - 1];
	else return 1;
}
bool Entity::getUp(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_row - 1 >= 0) return game_Maze[mtr_row - 1][mtr_col];
	else return 1;
}
bool Entity::getDown(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_row + 1 < game_Maze.size()) return game_Maze[mtr_row + 1][mtr_col];
	else return 1;
}
void Entity::keepInside(){
	auto coords = Entity::getCurrentBlockCoords();
	if(xpos + destR.w >= Game::width){
		xpos = Game::width - Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos + destR.h >= Game::height){
		ypos = Game::height - Game::block_h / 2 - destR.h / 2;
	}
	else if(xpos <= 0){
		xpos = Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos <= 0){
		ypos = Game::block_h / 2 - destR.h / 2;
	}
}
pair<int, int> Entity::getAutoBlockCoords(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(mtr_row % 2 == 0 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 1 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 0 and mtr_col % 2 == 1){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
	}
	else return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
}
pair<int, int> Entity::getAutoBlockCoords(int block_num){
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(mtr_row % 2 == 0 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 1 and mtr_col % 2 == 0){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 0 and mtr_col % 2 == 1){
		return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness), (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
	}
	else return { (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
}