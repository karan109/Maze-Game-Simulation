#include "Automated.hpp"
#include "Game.hpp"
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