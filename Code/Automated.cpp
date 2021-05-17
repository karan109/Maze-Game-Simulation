#include "Automated.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Stone.hpp"
#include "Entities.hpp"
#include "Graph.hpp"

Automated::Automated(const char * texturesheet, SDL_Rect srcR_param, int start) : Entity(texturesheet, srcR_param, start){

}
// void Automated::print_path(){
// 	vector<int> temp;
// 	while(!path.empty()){
// 		int front = path.front();
// 		temp.push_back(front);
// 		cout<<front<<" ";
// 		path.pop();
// 	}
// 	for(auto vertex : temp){
// 		path.push(vertex);
// 	}
// 	cout << endl;
// 	// cout<<endl<<endl<<endl;
// }
// void Automated::set_dest(int dest_param){
// 	while (!path.empty()){
// 		path.pop();
// 	}
// 	dest = dest_param;
// 	int init = Entity::getBlock();
// 	auto path_vector = Game::game_maze->graph.getPath(init, dest);
// 	for(auto vertex : path_vector){
// 		path.push(vertex);
// 	}
// 	current = path.front();
// 	path.pop();
// }
// void Automated::set_stones(){
// 	vector<int> points;
// 	points.push_back(getBlock());
// 	for(auto & stone: * Game::entities->stones){
// 		points.push_back(stone->getBlock());
// 	}
// 	auto adj = Game::game_maze->graph.getAdjMtr(points);
// 	auto check = Game::game_maze->graph.permute(Game::entities->stones->size());
// 	vector<int> indices;
// 	int cost = INT_MAX;
// 	vector<int> destination = {Game::rows * Game::cols - 1};
// 	for(auto u : check){
// 		int temp_cost = adj[0][u[0]] + Game::game_maze->graph.getDistances(points[u[u.size()-1]], destination)[0];
// 		for(int i=1;i < u.size();i++){
// 			temp_cost += adj[u[i]][u[i-1]];
// 		}
// 		if(temp_cost < cost){
// 			cost = temp_cost;
// 			indices = u;
// 		}
// 	}
// 	vector<int> path_vector;
// 	path_vector = Game::game_maze->graph.getPath(getBlock(), points[indices[0]]);
// 	for(int i=1;i<indices.size();i++){
// 		auto temp_path = Game::game_maze->graph.getPath(points[indices[i-1]], points[indices[i]]);
// 		for(int j=1;j<temp_path.size();j++){
// 			path_vector.push_back(temp_path[j]);
// 		}
// 	}
// 	for(auto vertex: Game::game_maze->graph.getPath(points[indices[indices.size()-1]], Game::rows * Game::cols - 1)){
// 		path_vector.push_back(vertex);
// 	}
// 	for(auto vertex : path_vector){
// 		path.push(vertex);
// 	}
// 	current = path.front();
// 	path.pop();
// }


// void Automated::set_dest(Entity * target_param){
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

// int Automated::switch_dir(int temp_dir, int current) {
// 	int next = INT_MIN;
// 	if (temp_dir == 1) {
// 		next = current + 1;
// 		xv = mag; 
// 	} 
// 	if (temp_dir == 2) {
// 		next = current + Game::cols;
// 		yv = mag; 
// 	}
// 	if (temp_dir == 3) {
// 		next = current - 1;
// 		xv = -mag; 
// 	}
// 	if (temp_dir == 4) {
// 		next = current - Game::cols;
// 		yv = -mag; 
// 	}
// 	return next;
// }


// void Automated::set_path_mode2() {

// 	int current = getBlock();
	
// 	// empty existing path
// 	while(!path.empty()) {
// 		path.pop();
// 	}

// 	vector <int> temp;

// 	if (xv == mag and yv == 0) {
// 		if (Entity::can_go_right(current)) temp.push_back(1);
// 		if (Entity::can_go_down(current)) temp.push_back(2);
// 		// if (Entity::can_go_left(current) and x!= 3) temp.push_back(3);
// 		if (Entity::can_go_up(current)) temp.push_back(4);
// 	}

// 	if (xv == -mag and yv == 0) {
// 		// if (Entity::can_go_right(current) and x != 1) temp.push_back(1);
// 		if (Entity::can_go_down(current)) temp.push_back(2);
// 		if (Entity::can_go_left(current)) temp.push_back(3);
// 		if (Entity::can_go_up(current)) temp.push_back(4);
// 	}

// 	if (yv == mag and xv == 0) {
// 		if (Entity::can_go_right(current)) temp.push_back(1);
// 		if (Entity::can_go_down(current)) temp.push_back(2);
// 		if (Entity::can_go_left(current)) temp.push_back(3);
// 		// if (Entity::can_go_up(current)and x!=4) temp.push_back(4);
// 	}

// 	if (yv == -mag and xv == 0) {
// 		if (Entity::can_go_right(current)) temp.push_back(1);
// 		// if (Entity::can_go_down(current) and x!=2) temp.push_back(2);
// 		if (Entity::can_go_left(current)) temp.push_back(3);
// 		if (Entity::can_go_up(current)) temp.push_back(4);
// 	}

// 	if (xv == 0 and yv == 0) {
// 		if (Entity::can_go_right(current)) temp.push_back(1);
// 		if (Entity::can_go_down(current)) temp.push_back(2);
// 		if (Entity::can_go_left(current)) temp.push_back(3);
// 		if (Entity::can_go_up(current)) temp.push_back(4);
// 	}

// 	// assert(temp.size()!=0);

// 	int temp_dir = temp[rand() % temp.size()];

// 	xv = 0;
// 	yv = 0;

// 	int next = switch_dir(temp_dir, current);


// 	// cout << "block: " << current << " xv: " << xv << " yv: " << yv << " next: " << next << " " << temp_dir << endl;
	
// 	path.push(next);
// }



// void Automated::set_path_mode3(Entity * scary_target) {

// 	auto & graph = Game::game_maze->graph;

// 	int current = getBlock();
// 	int scary_block = scary_target->getBlock();
	
// 	// empty existing path
// 	while(!path.empty()) {
// 		path.pop();
// 	}

// 	vector <int> temp;
// 	int next = current;


// 	if (Entity::can_go_right(current)) temp.push_back(1);
// 	if (Entity::can_go_down(current)) temp.push_back(2);
// 	if (Entity::can_go_left(current)) temp.push_back(3);
// 	if (Entity::can_go_up(current)) temp.push_back(4);	

// 	// assert(temp.size()!=0);

// 	// int temp_dir = temp[rand() % temp.size()];

// 	int temp_dir = 0;
// 	int max_distance = graph.distance(current, scary_block);
// 	bool a[5] = {0};

// 	for (int i = 0; i < temp.size() ; ++i) {
// 		int dir = temp[i];
// 		int d;
// 		if (dir == 1) {
// 			a[1] = 1;
// 			d = graph.distance(current + 1, scary_block);
// 			if (d > max_distance) {
// 				max_distance = d;
// 				temp_dir = 1;
// 			}
// 		}
// 		if (dir == 2) {
// 			a[2] = 1;
// 			d = graph.distance(current + Game::cols, scary_block);
// 			if (d > max_distance) {
// 				max_distance = d;
// 				temp_dir = 2;
// 			}
// 		}
// 		if (dir == 3) {
// 			a[3] = 1;
// 			d = graph.distance(current - 1, scary_block);
// 			if (d > max_distance) {
// 				max_distance = d;
// 				temp_dir = 3;
// 			}
// 		}
// 		if (dir == 4) {
// 			a[4] = 1;
// 			d = graph.distance(current - Game::cols, scary_block);
// 			if (d > max_distance) {
// 				max_distance = d;
// 				temp_dir = 4;
// 			}
// 		}
// 	}

// 	if (temp_dir == 1) {
// 		next = current + 1;
// 		xv = mag;
// 		yv = 0; 
// 	} 
// 	if (temp_dir == 2) {
// 		next = current + Game::cols;
// 		yv = mag; 
// 		xv = 0;
// 	}
// 	if (temp_dir == 3) {
// 		next = current - 1;
// 		xv = -mag;
// 		yv = 0; 
// 	}
// 	if (temp_dir == 4) {
// 		next = current - Game::cols;
// 		yv = -mag;
// 		xv = 0; 
// 	}
// 	if (temp_dir == 0) {
// 		//go according to velocity if possible to go
// 		if (xv == mag and a[1] == 1) {
// 			next = current + 1;
// 		}
// 		else if (yv == mag and a[2] == 1) {
// 			next = current + Game::cols;
// 		}
// 		else if (xv == -mag and a[3] == 1) {
// 			next = current - 1;
// 		}
// 		else if (yv == -mag and a[4] == 1) {
// 			next = current - Game::cols;
// 		}
// 		else {
// 			int go_randomly = temp[rand() % temp.size()];
// 			next = switch_dir(go_randomly, current);
// 		}
// 	}
// 	// if nothing else works just stay where you are
// 	// xv = 0
// 	// yv = 0
// 	path.push(next);
// }


// void Automated::set_mode (int mode_id, Entity * target_param) {
// 	if (mode_id == 0) {
// 		mode = 0;
// 		target = target_param;
// 		Automated::set_dest(target_param);
// 	}
// 	if (mode_id == 3) {
// 		mode = 3;
// 		scary_target = target_param;
// 		Automated::set_path_mode3(scary_target);
// 	}
// }

// void Automated::set_mode (int mode_id, int dest_param) {
// 	if (mode_id == 1) {
// 		mode = 1;
// 		dest = dest_param;
// 		Automated::set_dest(dest_param);
// 	}
// }

// void Automated::set_mode(int mode_id) {
// 	if (mode_id == 2) {
// 		mode = 2;
// 		// set initial velocity
// 		set_path_mode2();
// 	}

// 	if (mode_id == 4) {
// 		mode = 4;
// 		Automated::set_stones();
// 	}

// }


// void Automated::set_mode_id(int mode_id) {
// 	mode = mode_id;
// }

// // different from player
// void Automated::handle_wall_collisions() {
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
// }

// int Automated::getNext() {
// 	int current = getBlock();
// 	int next = INT_MIN;
// 	if(!path.empty()){
// 		next = path.front();
// 		if(next == current){
// 			path.pop();
// 			if (!path.empty()) {
// 				next = path.front();
// 			}
// 			else {
// 				next = INT_MIN;
// 			}
// 		}
// 	}
// 	return next;
// }

// int Automated::manhattan_distance() {
// 	auto coords = getAutoBlockCoords();
// 	int centre_x = xpos + destR.w / 2;
// 	int centre_y = ypos + destR.h / 2;
// 	int block_centre_y = coords.first + Game::block_h / 2;
// 	int block_centre_x = coords.second + Game::block_w / 2;
// 	return abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y);
// }


// void Automated::switch_next(int current, int next) {

// 	auto coords = getAutoBlockCoords();

// 	if(next == current + 1){
// 		xv = mag;
// 		yv = 0;
// 		ypos = coords.first + Game::block_h / 2 - destR.h / 2;
// 	}
// 	else if(next == current - 1){
// 		xv = -mag;
// 		yv = 0;
// 		ypos = coords.first + Game::block_h / 2 - destR.h / 2;
// 	}
// 	else if(next == current + Game::cols){
// 		xv = 0;
// 		yv = mag;
// 		xpos = coords.second + Game::block_w / 2 - destR.w / 2;
// 	}
// 	else if(next == current - Game::cols){
// 		xv = 0;
// 		yv = -mag;
// 		xpos = coords.second + Game::block_w / 2 - destR.w / 2;
// 	}
// }

// void Automated::update_position() {
// 	xpos += xv * speed;
// 	ypos += yv * speed;	
// 	destR.x = xpos;
// 	destR.y = ypos;
// }


// bool Automated::is_at_centre () {
// 	auto coords = getAutoBlockCoords();
// 	int centre_x = xpos + destR.w / 2;
// 	int centre_y = ypos + destR.h / 2;
// 	int block_centre_y = coords.first + Game::block_h / 2;
// 	int block_centre_x = coords.second + Game::block_w / 2;
// 	if(abs(centre_x - block_centre_x) + abs(centre_y - block_centre_y) <= 4){
// 		return true;
// 	}
// 	return false;
// }

// void Automated::empty_the_path() {
// 	while (!path.empty()) {
// 		path.pop();
// 	}
// }
// // at centre of current node
// void Automated::set_pos_at_centre() {
// 	auto coords = getAutoBlockCoords();
// 	xpos = coords.second + Game::block_w / 2 - destR.w / 2;
// 	ypos = coords.first + Game::block_h / 2 - destR.h / 2;
// 	destR.x = xpos;
// 	destR.y = ypos;
// }
// // at centre of node start
// void Automated::set_pos (int start) {
// 	auto coords = getAutoBlockCoords(start);
// 	destR.x = coords.second + Game::block_w / 2 - Game::player_w / 2;
// 	destR.y = coords.first + Game::block_h / 2 - Game::player_h / 2;
// 	xpos = destR.x;
// 	ypos = destR.y;
// }

// void Automated::set_velocity_zero() {
// 	xv = 0;
// 	yv = 0;
// }


// void Automated::Update0() {

// 	if(target == nullptr) return;
// 	// changes path as target moves 
// 	Automated::set_dest(target);
	
// 	int current = getBlock();
// 	int next = getNext();

// 	// if (next == INT_MIN) return; // why idk

// 	if(manhattan_distance() <= 4){
// 		switch_next(current, next);
// 	}

// 	update_position();
// }

// void Automated::Update1() {

// 	if(scatter_reached) return;

// 	int current = getBlock();
// 	int next = getNext();

// 	if(manhattan_distance() <= 4){
// 		if(path.empty()){
// 			set_pos_at_centre();
// 			set_velocity_zero();
// 			scatter_reached = true;
// 			return;
// 		}
// 		switch_next(current, next);
// 	}

// 	update_position();
// }

// void Automated::Update2() {

// 	srand(time(0));

// 	int current = getBlock();
// 	int next = getNext();

// 	if(manhattan_distance() <= 4){

// 		if(path.empty()){
// 			set_path_mode2();
// 			set_pos_at_centre();
// 			return;
// 		}
// 		switch_next(current, next);
// 	}

// 	update_position();
// }	



// void Automated::Update3() {

// 	srand(time(0));

// 	int current = getBlock();
// 	int next = getNext();

// 	if(manhattan_distance() <= 4){

// 		if(path.empty()){

// 			set_path_mode3(scary_target);
// 			set_pos_at_centre();
// 			return;
// 		}

// 		switch_next(current, next);
// 	}

// 	update_position();
// }	


// void Automated::Update4() {
// 	if(drone_reached) return;

// 	int current = getBlock();
// 	int next = getNext();

// 	if(manhattan_distance() <= 4){

// 		if(path.empty()){
// 			set_pos_at_centre();
// 			set_velocity_zero();
// 			drone_reached = true;
// 			return;
// 		}
// 		switch_next(current, next);
// 	}
// 	update_position();
// }


// void Automated::Update(){

// 	time_update();

// 	Entity::keepInside();
// 	handle_wall_collisions();

// 	if (mode == 0) {
// 		Update0();

// 	}


// 	if (mode == 1) {
// 		Update1();
// 	}


// 	if (mode == 2) {
// 		Update2();

// 	}



// 	if (mode == 3) {
// 		Update3();
		
// 	}

// 	if (mode == 4) {
// 		Update4();
		
// 	}

// }





// bool Automated::change_mode(int mode_id) {
// 	if (!is_at_centre() ) return false;
	
// 	set_pos_at_centre();
// 	set_velocity_zero();

// 	empty_the_path();

// 	if (mode_id == 0) {
// 		set_mode(0, target);
// 	}
// 	if (mode_id == 1) {
// 		set_mode(1, dest);
// 	}

// 	if (mode_id == 2) {
// 		set_mode(2);
// 	}

// 	if (mode_id == 3) {
// 		set_mode(3, scary_target);
// 	}

// 	if (mode_id == 4) {
// 		set_mode(4);
// 	}
// 	return true;

// }

// void Automated::restart() {
// 	set_pos(start_node);
// 	change_mode(mode);
// }



