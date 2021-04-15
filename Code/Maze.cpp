#include "Texture.hpp"
#include "Maze.hpp"
#include "Graph.hpp"

Maze::Maze(){
	dirt = Texture::LoadTexture("../Images/dirt.png");
	grass = Texture::LoadTexture("../Images/grass.png");
	water = Texture::LoadTexture("../Images/water.png");
	Graph g(10, 10, 0);
	auto lvl1 = g.exportMtr;
	LoadMaze(lvl1);
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.w = 32;
	dest.h = 32;
	dest.x = 0;
	dest.y = 0;
}
Maze::~Maze(){
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(dirt);
}
void Maze::LoadMaze(vector<vector<int>> arr){
	game_Maze = arr;
}
void Maze::DrawMaze(){
	int type = 0;
	for(int i = 0; i < game_Maze.size(); i++){
		for(int j = 0; j < game_Maze[0].size(); j++){
			type = game_Maze[i][j];
			dest.x = j * 32;
			dest.y = i * 32;
			if(type == 0){
				Texture::Draw(water, src, dest);
			}
			else if(type == 1){
				Texture::Draw(grass, src, dest);
			}
			else{
				Texture::Draw(dirt, src, dest);
			}
		}
	}
}