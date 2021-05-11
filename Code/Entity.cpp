#include "Game.hpp"
#include "Entity.hpp"
#include "Texture.hpp"

#include "Collision.hpp"
#include "Stone.hpp"
#include "Entities.hpp"
#include "Graph.hpp"


// -------------------------------------------------------CONSTRUCTOR AND RELATED FUNCTIONS-------------------------------------------------------------------------------------



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
	start_node = start;
	retreat_node = start;
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
// not the velocity
void Entity::change_objTexture( SDL_Texture * tex ,SDL_Rect srcR_param, SDL_Rect destR_param) {
	objTexture = tex;
	srcR = srcR_param;
	destR = destR_param;
	xpos = destR.x;
	ypos = destR.y;
}
// not the velocity
void Entity::change_objTexture( const char * texturesheet ,SDL_Rect srcR_param, SDL_Rect destR_param) {
	objTexture = Texture::LoadTexture(texturesheet);
	srcR = srcR_param;
	destR = destR_param;
	xpos = destR.x;
	ypos = destR.y;
}

// void Entity::Update(){
// }

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


// ------------------------------------------------------SET MODE CONSTRUCTORS--------------------------------------------------------------------------------------


void Entity::set_mode (int mode_id, Entity * target_param) {
	if (mode_id == 0) {
		mode = 0;
		target = target_param;
		Entity::set_dest(target_param);
	}
	if (mode_id == 3) {
		mode = 3;
		scary_target = target_param;
		Entity::set_path_mode3(scary_target);
	}
}

void Entity::set_mode (int mode_id, int dest_param) {
	if (mode_id == 1) {
		mode = 1;
		dest = dest_param;
		Entity::set_dest(dest_param);
	}
}

void Entity::set_mode(int mode_id) {
	if (mode_id == 2) {
		mode = 2;
		// set initial velocity
		set_path_mode2();
	}

	if (mode_id == 4) {
		mode = 4;
		Entity::set_stones();
	}

}


void Entity::set_mode_id(int mode_id) {
	mode = mode_id;
}


// ------------------------------------------------------GLOBAL UPDATE AND CHANGE MODE--------------------------------------------------------------------------------------


void Entity::Update(){

	time_update();

	Entity::keepInside();
	handle_wall_collisions();

	if (mode == 0) {
		Update0();
	}

	if (mode == 1) {
		Update1();
	}

	if (mode == 2) {
		Update2();
	}

	if (mode == 3) {
		Update3();
	}

	if (mode == 4) {
		Update4();
	}

}



bool Entity::change_mode(int mode_id) {
	if (!is_at_centre() ) return false;
	
	set_pos_at_centre();
	set_velocity_zero();

	empty_the_path();

	if (mode_id == 0) {
		set_mode(0, target);
	}
	if (mode_id == 1) {
		set_mode(1, dest);
	}

	if (mode_id == 2) {
		set_mode(2);
	}

	if (mode_id == 3) {
		set_mode(3, scary_target);
	}

	if (mode_id == 4) {
		set_mode(4);
	}
	return true;

}


// ------------------------------------------------------SET SMALL STUFF AND RESTART--------------------------------------------------------------------------------------


void Entity::restart() {
	set_pos(start_node);
	// change_mode(mode);
}


void Entity::set_starting_node(int start) {
	auto coords = getAutoBlockCoords(start);
	destR.x = coords.second + Game::block_w / 2 - Game::player_w / 2;
	destR.y = coords.first + Game::block_h / 2 - Game::player_h / 2;
	xpos = destR.x;
	ypos = destR.y;
	xv = 0;
	yv = 0;
}

// at centre of node start
void Entity::set_pos (int start) {
	auto coords = getAutoBlockCoords(start);
	destR.x = coords.second + Game::block_w / 2 - Game::player_w / 2;
	destR.y = coords.first + Game::block_h / 2 - Game::player_h / 2;
	xpos = destR.x;
	ypos = destR.y;
}


// at centre of current node
void Entity::set_pos_at_centre() {
	auto coords = getAutoBlockCoords();
	xpos = coords.second + Game::block_w / 2 - destR.w / 2;
	ypos = coords.first + Game::block_h / 2 - destR.h / 2;
	destR.x = xpos;
	destR.y = ypos;
}


void Entity::set_velocity_zero() {
	xv = 0;
	yv = 0;
}

void Entity::set_dest(int dest_param){
	while (!path.empty()){
		path.pop();
	}
	dest = dest_param;
	int init = Entity::getBlock();
	auto path_vector = Game::game_maze->graph.getPath(init, dest);
	for(auto vertex : path_vector){
		path.push(vertex);
	}
	current = path.front();
	path.pop();
}

void Entity::set_dest(Entity * target_param){
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



// ------------------------------------------------------UPDATE SMALL STUFF--------------------------------------------------------------------------------------


void Entity::time_update() {
	entity_counter++;
	entity_time = (double) entity_counter / Game::FPS;
}


void Entity::update_position() {
	xpos += xv * speed;
	ypos += yv * speed;	
	destR.x = xpos;
	destR.y = ypos;
}





// ------------------------------------------------------SET PATH (MODE)--------------------------------------------------------------------------------------


void Entity::set_path_mode2() {

	int current = getBlock();
	
	// empty existing path
	while(!path.empty()) {
		path.pop();
	}

	vector <int> temp;

	if (xv == mag and yv == 0) {
		if (Entity::can_go_right(current)) temp.push_back(1);
		if (Entity::can_go_down(current)) temp.push_back(2);
		// if (Entity::can_go_left(current) and x!= 3) temp.push_back(3);
		if (Entity::can_go_up(current)) temp.push_back(4);
	}

	if (xv == -mag and yv == 0) {
		// if (Entity::can_go_right(current) and x != 1) temp.push_back(1);
		if (Entity::can_go_down(current)) temp.push_back(2);
		if (Entity::can_go_left(current)) temp.push_back(3);
		if (Entity::can_go_up(current)) temp.push_back(4);
	}

	if (yv == mag and xv == 0) {
		if (Entity::can_go_right(current)) temp.push_back(1);
		if (Entity::can_go_down(current)) temp.push_back(2);
		if (Entity::can_go_left(current)) temp.push_back(3);
		// if (Entity::can_go_up(current)and x!=4) temp.push_back(4);
	}

	if (yv == -mag and xv == 0) {
		if (Entity::can_go_right(current)) temp.push_back(1);
		// if (Entity::can_go_down(current) and x!=2) temp.push_back(2);
		if (Entity::can_go_left(current)) temp.push_back(3);
		if (Entity::can_go_up(current)) temp.push_back(4);
	}

	if (xv == 0 and yv == 0) {
		if (Entity::can_go_right(current)) temp.push_back(1);
		if (Entity::can_go_down(current)) temp.push_back(2);
		if (Entity::can_go_left(current)) temp.push_back(3);
		if (Entity::can_go_up(current)) temp.push_back(4);
	}

	// assert(temp.size()!=0);

	int temp_dir = temp[rand() % temp.size()];

	xv = 0;
	yv = 0;

	int next = switch_dir(temp_dir, current);


	// cout << "block: " << current << " xv: " << xv << " yv: " << yv << " next: " << next << " " << temp_dir << endl;
	
	path.push(next);
}



void Entity::set_path_mode3(Entity * scary_target) {

	auto & graph = Game::game_maze->graph;

	int current = getBlock();
	int scary_block = scary_target->getBlock();
	
	// empty existing path
	while(!path.empty()) {
		path.pop();
	}

	vector <int> temp;
	int next = current;


	if (Entity::can_go_right(current)) temp.push_back(1);
	if (Entity::can_go_down(current)) temp.push_back(2);
	if (Entity::can_go_left(current)) temp.push_back(3);
	if (Entity::can_go_up(current)) temp.push_back(4);	

	// assert(temp.size()!=0);

	// int temp_dir = temp[rand() % temp.size()];

	int temp_dir = 0;
	int max_distance = graph.distance(current, scary_block);
	bool a[5] = {0};

	for (int i = 0; i < temp.size() ; ++i) {
		int dir = temp[i];
		int d;
		if (dir == 1) {
			a[1] = 1;
			d = graph.distance(current + 1, scary_block);
			if (d > max_distance) {
				max_distance = d;
				temp_dir = 1;
			}
		}
		if (dir == 2) {
			a[2] = 1;
			d = graph.distance(current + Game::cols, scary_block);
			if (d > max_distance) {
				max_distance = d;
				temp_dir = 2;
			}
		}
		if (dir == 3) {
			a[3] = 1;
			d = graph.distance(current - 1, scary_block);
			if (d > max_distance) {
				max_distance = d;
				temp_dir = 3;
			}
		}
		if (dir == 4) {
			a[4] = 1;
			d = graph.distance(current - Game::cols, scary_block);
			if (d > max_distance) {
				max_distance = d;
				temp_dir = 4;
			}
		}
	}

	if (temp_dir == 1) {
		next = current + 1;
		xv = mag;
		yv = 0; 
	} 
	if (temp_dir == 2) {
		next = current + Game::cols;
		yv = mag; 
		xv = 0;
	}
	if (temp_dir == 3) {
		next = current - 1;
		xv = -mag;
		yv = 0; 
	}
	if (temp_dir == 4) {
		next = current - Game::cols;
		yv = -mag;
		xv = 0; 
	}
	if (temp_dir == 0) {
		//go according to velocity if possible to go
		if (xv == mag and a[1] == 1) {
			next = current + 1;
		}
		else if (yv == mag and a[2] == 1) {
			next = current + Game::cols;
		}
		else if (xv == -mag and a[3] == 1) {
			next = current - 1;
		}
		else if (yv == -mag and a[4] == 1) {
			next = current - Game::cols;
		}
		else {
			int go_randomly = temp[rand() % temp.size()];
			next = switch_dir(go_randomly, current);
		}
	}
	// if nothing else works just stay where you are
	// xv = 0
	// yv = 0
	path.push(next);
}



void Entity::set_stones(){
	vector<int> points;
	points.push_back(getBlock());
	for(auto & stone: * Game::entities->stones){
		points.push_back(stone->getBlock());
	}
	auto adj = Game::game_maze->graph.getAdjMtr(points);
	auto check = Game::game_maze->graph.permute(Game::entities->stones->size());
	vector<int> indices;
	int cost = INT_MAX;
	vector<int> destination = {Game::rows * Game::cols - 1};
	for(auto u : check){
		int temp_cost = adj[0][u[0]] + Game::game_maze->graph.getDistances(points[u[u.size()-1]], destination)[0];
		for(int i=1;i < u.size();i++){
			temp_cost += adj[u[i]][u[i-1]];
		}
		if(temp_cost < cost){
			cost = temp_cost;
			indices = u;
		}
	}
	vector<int> path_vector;
	path_vector = Game::game_maze->graph.getPath(getBlock(), points[indices[0]]);
	for(int i=1;i<indices.size();i++){
		auto temp_path = Game::game_maze->graph.getPath(points[indices[i-1]], points[indices[i]]);
		for(int j=1;j<temp_path.size();j++){
			path_vector.push_back(temp_path[j]);
		}
	}
	for(auto vertex: Game::game_maze->graph.getPath(points[indices[indices.size()-1]], Game::rows * Game::cols - 1)){
		path_vector.push_back(vertex);
	}
	for(auto vertex : path_vector){
		path.push(vertex);
	}
	current = path.front();
	path.pop();
}







// ------------------------------------------------------KEEP INSIDE AND HANDLE COLLISIONS--------------------------------------------------------------------------------------



// different from player
void Entity::handle_wall_collisions() {
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
}


// Keep entity inside main window
void Entity::keepInside(){
	int delay = 5;
	auto coords = Entity::getCurrentBlockCoords();
	if(xpos + destR.w >= Game::width - Game::wall_thickness){
		wall_ct++;
		if(wall_ct >= delay)
			Mix_PlayChannel( -1, Game::gScratch, 0 );
		xpos = Game::width - Game::wall_thickness - Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos + destR.h >= Game::height - Game::wall_thickness){
		wall_ct++;
		if(wall_ct >= delay)
			Mix_PlayChannel( -1, Game::gScratch, 0 );
		ypos = Game::height - Game::wall_thickness - Game::block_h / 2 - destR.h / 2;
	}
	else if(xpos <= Game::wall_thickness){
		wall_ct++;
		if(wall_ct >= delay)
			Mix_PlayChannel( -1, Game::gScratch, 0 );
		xpos = Game::wall_thickness + Game::block_w / 2 - destR.w / 2;
	}
	else if(ypos <= Game::menu){
		wall_ct++;
		if(wall_ct >= delay)
			Mix_PlayChannel( -1, Game::gScratch, 0 );
		ypos = Game::menu + Game::block_h / 2 - destR.h / 2;
	}
}



// ------------------------------------------------------UPDATE AUXILARIES--------------------------------------------------------------------------------------



int Entity::getNext() {
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
	return next;
}

int Entity::manhattan_distance() {
	auto coords = getAutoBlockCoords();
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;
	return abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y);
}


int Entity::switch_dir(int temp_dir, int current) {
	int next = INT_MIN;
	if (temp_dir == 1) {
		next = current + 1;
		xv = mag; 
	} 
	if (temp_dir == 2) {
		next = current + Game::cols;
		yv = mag; 
	}
	if (temp_dir == 3) {
		next = current - 1;
		xv = -mag; 
	}
	if (temp_dir == 4) {
		next = current - Game::cols;
		yv = -mag; 
	}
	return next;
}


void Entity::switch_next(int current, int next) {

	auto coords = getAutoBlockCoords();

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

// ------------------------------------------------------UPDATE (MODE)--------------------------------------------------------------------------------------


void Entity::Update0() {

	if(target == nullptr) return;
	// changes path as target moves 
	Entity::set_dest(target);
	
	int current = getBlock();
	int next = getNext();

	// if (next == INT_MIN) return; // why idk

	if(manhattan_distance() <= 4){
		switch_next(current, next);
	}

	update_position();
}

void Entity::Update1() {

	if(scatter_reached) return;

	int current = getBlock();
	int next = getNext();

	if(manhattan_distance() <= 4){
		if(path.empty()){
			set_pos_at_centre();
			set_velocity_zero();
			scatter_reached = true;
			return;
		}
		switch_next(current, next);
	}

	update_position();
}

void Entity::Update2() {

	srand(time(0));

	int current = getBlock();
	int next = getNext();

	if(manhattan_distance() <= 4){

		if(path.empty()){
			set_path_mode2();
			set_pos_at_centre();
			return;
		}
		switch_next(current, next);
	}

	update_position();
}	



void Entity::Update3() {

	srand(time(0));

	int current = getBlock();
	int next = getNext();

	if(manhattan_distance() <= 4){

		if(path.empty()){

			set_path_mode3(scary_target);
			set_pos_at_centre();
			return;
		}

		switch_next(current, next);
	}

	update_position();
}	


void Entity::Update4() {
	if(drone_reached) return;

	int current = getBlock();
	int next = getNext();

	if(manhattan_distance() <= 4){

		if(path.empty()){
			set_pos_at_centre();
			set_velocity_zero();
			drone_reached = true;
			return;
		}
		switch_next(current, next);
	}
	update_position();
}


// --------------------------------------------------------SMALL PATH and related FUNCTIONS------------------------------------------------------------------------------------


int Entity::distance(Entity * e1, Entity * e2) {
	auto & graph = Game::game_maze->graph;

	int n1 = e1->getBlock();
	int n2 = e2->getBlock();
	
	return graph.distance(n1, n2);

} 

void Entity::empty_the_path() {
	while (!path.empty()) {
		path.pop();
	}
}

void Entity::print_path(){
	vector<int> temp;
	while(!path.empty()){
		int front = path.front();
		temp.push_back(front);
		cout<<front<<" ";
		path.pop();
	}
	for(auto vertex : temp){
		path.push(vertex);
	}
	cout << endl;
	// cout<<endl<<endl<<endl;
}


bool Entity::is_at_centre () {
	auto coords = getAutoBlockCoords();
	int centre_x = xpos + destR.w / 2;
	int centre_y = ypos + destR.h / 2;
	int block_centre_y = coords.first + Game::block_h / 2;
	int block_centre_x = coords.second + Game::block_w / 2;
	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){
		return true;
	}
	return false;
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





// -------------------------------------------------------------------BLOCK AND COORDINATES-------------------------------------------------------------------------

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



// -------------------------------------------------------------------CAN GO IN DIRECTION-------------------------------------------------------------------------




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











// ------------------------------------------------------THOSE NOT USED--------------------------------------------------------------------------------------


bool Entity::in_sight(Entity * e1, Entity * e2) {
	auto & game_maze = Game::game_maze->game_Maze;

	int n1 = e1->getBlock();
	int row1 = n1 / Game::cols;
	int col1 = n1 % Game::cols;

	int n2 = e2->getBlock();
	int row2 = n2 / Game::cols;
	int col2 = n2 % Game::cols;

	if (row1 == row2) {
		for (int i = min(col1, col2) + 1 ; i < max (col1, col2) ; ++i) {
			if (game_maze[row1][i] == 1) return false;
		}
		return true;
	}
	else if (col1 == col2) {
		for (int i = min(row1, row2) + 1 ; i < max (row1, row2) ; ++i) {
			if (game_maze[i][col1] == 1) return false;
		}
		return true;
	}
	return false;
}


int Entity::is_frightened(Entity * e1, Entity * e2) {
	
	int n1 = e1->getBlock();
	int row1 = n1 / Game::cols;
	int col1 = n1 % Game::cols;
	int xv1 = e1->getXV();
	int x1 = e1->getX();
	int yv1 = e1->getYV();
	int y1 = e1->getY();

	int positive_xv1 = abs(xv1);
	int negative_xv1 = -1*abs(xv1);
	int positive_yv1 = abs(yv1);
	int negative_yv1 = -1*abs(yv1);

	int n2 = e2->getBlock();
	int row2 = n2 / Game::cols;
	int col2 = n2 % Game::cols;
	int xv2 = e2->getXV();
	int x2 = e2->getX();
	int yv2 = e2->getYV();
	int y2 = e2->getY();

	
	if (in_sight(e1, e2) and distance(e1, e2) <= 7) {
		if (row1 == row2) {
			if (x1 - x2 >= 0 and xv1 - xv2 < 0) {
				//change xv1 from - to + cannot go left
				// e1->setXV(positive_xv1);
				return 3;
			}
			else if (x1 - x2 < 0 and xv1 - xv2 > 0) {
				//change xv1 from + to - cannot go right
				// e1->setXV(negtive_xv1);
				return 1;
			}
		}
		if (col1 == col2) {
			if (y1 - y2 >= 0 and yv1 - yv2 < 0) {
				//change yv1 from - to + cannot go down
				// e1->setYV(positive_yv1);
				return 2;
			}
			if (y1 - y2 < 0 and yv1 - yv2 >= 0) {
				//change xv1 from + to - cannot go up
				// e1->setYV(negative_yv1);
				return 4;
			}
		}
	}
	return 0;
}