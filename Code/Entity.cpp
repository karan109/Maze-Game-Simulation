#include "Game.hpp"
#include "Entity.hpp"
#include "Texture.hpp"

// Constructor when start node number is given (for moving entities)
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

// Constructor when start coordinates are given as Rect (destR_param)
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

// Returns bounding box
SDL_Rect Entity::getBB(){
	return destR;
}

// Get currrent node number ie the big block number
int Entity::getBlock(){
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int row = (centre_y - Game::menu) / (Game::block_h + Game::wall_thickness);
	int col = (centre_x - Game::wall_thickness) / (Game::block_w + Game::wall_thickness);
	return row * Game::cols + col;
}

// Get coords of current block
pair<int, int> Entity::getCurrentBlockCoords(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_row % 2 == 0 and mtr_col % 2 == 0){
		return { Game::menu + (mtr_row / 2) * (Game::block_h + Game::wall_thickness), Game::wall_thickness + (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 1 and mtr_col % 2 == 0){
		return { Game::menu + (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, Game::wall_thickness + (mtr_col / 2) * (Game::block_w + Game::wall_thickness) };
	}
	else if(mtr_row % 2 == 0 and mtr_col % 2 == 1){
		return { Game::menu + (mtr_row / 2) * (Game::block_h + Game::wall_thickness), Game::wall_thickness + (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
	}
	else return { Game::menu + (mtr_row / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h, Game::wall_thickness + (mtr_col / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w };
}

// 1 if wall is present towards right, 0 otherwise
// the right entry of whatever mtr block this entity is in. in case nothing on right then also return 1.
bool Entity::getRight(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_col + 1 < game_Maze[0].size()) return game_Maze[mtr_row][mtr_col + 1];
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
	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
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
	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
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
	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) mtr_row++;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) mtr_col++;
	if(mtr_row + 1 < game_Maze.size()) return game_Maze[mtr_row + 1][mtr_col];
	else return 1;
}

// Keep entity inside main window
void Entity::keepInside(){
	auto coords = Entity::getCurrentBlockCoords();
	if(xpos + destR.w >= Game::width - Game::wall_thickness){
		Mix_PlayChannel( -1, Game::gScratch, 0 );
		xpos = Game::width - Game::wall_thickness - Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos + destR.h >= Game::height - Game::wall_thickness){
		Mix_PlayChannel( -1, Game::gScratch, 0 );
		ypos = Game::height - Game::wall_thickness - Game::block_h / 2 - destR.h / 2;
	}
	else if(xpos <= Game::wall_thickness){
		Mix_PlayChannel( -1, Game::gScratch, 0 );
		xpos = Game::wall_thickness + Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos <= Game::menu){
		Mix_PlayChannel( -1, Game::gScratch, 0 );
		ypos = Game::menu + Game::block_h / 2 - destR.h / 2;
	}
}

// Coordinates of current approximate block (big block)
pair<int, int> Entity::getAutoBlockCoords(){
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	return { Game::menu + (row) * (Game::block_h + Game::wall_thickness), Game::wall_thickness + (col) * (Game::block_w + Game::wall_thickness) };

}

// Coordinates of a big block given its node number
pair<int, int> Entity::getAutoBlockCoords(int block_num){
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	return { Game::menu + (row) * (Game::block_h + Game::wall_thickness), Game::wall_thickness + (col) * (Game::block_w + Game::wall_thickness) };
}




bool Entity::can_go_right(int block_num) {
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	auto & game_Maze = Game::game_maze->game_Maze;

	if(mtr_col + 1 < game_Maze[0].size()) return !(game_Maze[mtr_row][mtr_col + 1]);
	else return 0;
}
bool Entity::can_go_left(int block_num) {
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	auto & game_Maze = Game::game_maze->game_Maze;

	if(mtr_col - 1 >= 0) return ! game_Maze[mtr_row][mtr_col - 1];
	else return 0;

}
bool Entity::can_go_up(int block_num) {
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	int mtr_row = row * 2;
	int mtr_col = col * 2;

	auto & game_Maze = Game::game_maze->game_Maze;

	if(mtr_row - 1 >= 0) return ! game_Maze[mtr_row - 1][mtr_col];
	else return 0;
}

bool Entity::can_go_down(int block_num) {
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	int mtr_row = row * 2;
	int mtr_col = col * 2;

	auto & game_Maze = Game::game_maze->game_Maze;

	if(mtr_row + 1 < game_Maze.size()) return !game_Maze[mtr_row + 1][mtr_col];
	else return 0;
}


bool Entity::is_inside_node() {
	int block_num = getBlock();
	int row = block_num / Game::cols;
	int col = block_num % Game::cols;
	auto & game_Maze = Game::game_maze->game_Maze;
	int mtr_row = row * 2;
	int mtr_col = col * 2;
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;

	if(centre_y >= (Game::menu + row * (Game::block_h + Game::wall_thickness) + Game::block_h) ) return false;
	if(centre_x >= (Game::wall_thickness + col * (Game::block_w + Game::wall_thickness) + Game::block_w) ) return false;
	return true;
}