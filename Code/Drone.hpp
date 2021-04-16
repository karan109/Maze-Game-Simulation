#pragma once

#include "Entity.hpp"

class Drone : public Entity{
public:
	Drone(SDL_Rect srcR_param, SDL_Rect destR_param, int dest);
	void Update() override;
private:
	queue<int> path;
	int current;
	pair<int, int> getAutoBlockCoords();
	void print_path(){
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
		cout<<endl;
	}
};