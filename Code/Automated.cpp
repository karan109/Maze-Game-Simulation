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

// void Automated::set_mode (int mode_id, Entity * target_param) {
// 	if (mode_id != 0) return;
// 	mode = 0;
// 	target = target_param;
// 	Automated::set_dest(target_param);
// }

// void Automated::set_mode (int mode_id, int dest_param) {
// 	if (mode_id != 1) return;
// 	mode = 1;
// 	dest = dest_param;
// 	Automated::set_dest(dest_param);
// }


// void Automated::set_mode(int mode_id) {
// 	if (mode_id == 2) {
// 		mode = 2;

// 		// set initial velocity
// 		xv = mag;
// 	}

// 	if (mode_id == 3) {
// 		mode = 3;
// 		Automated::set_stones();
// 	}

// }

// void Automated::set_mode3() {
// 	mode = 3;
// 	Automated::set_stones();
// }

void Automated::set_mode_id(int mode_id) {
	mode = mode_id;
}



void Automated::Update(){


	if (mode == 0) {


	}


	if (mode == 1) {

	}


	if (mode == 2) {


	}



	if (mode == 3) {


		
	}


}
