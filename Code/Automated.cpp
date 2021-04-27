#include "Automated.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Stone.hpp"
#include "Entities.hpp"
#include "Graph.hpp"

Automated::Automated(const char * texturesheet, SDL_Rect srcR_param, int start) : Entity(texturesheet, srcR_param, start){

}
void Automated::print_path(){
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
	cout<<endl<<endl<<endl;
}
void Automated::set_dest(int dest_param){
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
void Automated::set_stones(){
	vector<int> points;
	points.push_back(getBlock());
	for(auto & stone: * Game::entities->stones){
		points.push_back(stone->getBlock());
	}
	auto adj = Game::game_maze->graph.getAdjMtr(points);
	auto check = Game::game_maze->graph.permute(Game::entities->stones->size());
	vector<int> indices;
	int cost = INT_MAX;
	for(auto u : check){
		int temp_cost = adj[0][u[0]];
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
	for(auto vertex : path_vector){
		path.push(vertex);
	}
	current = path.front();
	path.pop();
}


void Automated::set_dest(Entity * target_param){
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

void Automated::set_mode (int mode_id, Entity * target_param) {
	if (mode_id != 0) return;
	mode = 0;
	target = target_param;
	Automated::set_dest(target_param);
}

void Automated::set_mode (int mode_id, int dest_param) {
	if (mode_id != 1) return;
	mode = 1;
	dest = dest_param;
	Automated::set_dest(dest_param);
}

void Automated::set_path_mode2() {

	// if (!path.empty()) return;

	// empty existing path
	while(!path.empty()) {
		path.pop();
	}

	vector <int> temp;
	int current = getBlock();
	int next = INT_MIN;


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


}

void Automated::set_mode(int mode_id) {
	if (mode_id == 2) {
		mode = 2;


		// set initial velocity
		set_path_mode2();
	}

	if (mode_id == 3) {
		mode = 3;
		Automated::set_stones();
	}

}


void Automated::set_mode_id(int mode_id) {
	mode = mode_id;
}

void Automated::Update0() {

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

void Automated::Update1(){}

void Automated::Update2() {
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

			set_path_mode2();

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



void Automated::Update3(){}


void Automated::Update(){


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


}
