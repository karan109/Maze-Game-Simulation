#include "Texture.hpp"
#include "Maze.hpp"
#include "Entities.hpp"
#include "Wall.hpp"
#include "Game.hpp"


Maze::Maze(){
	made = false;
	dirt = Texture::LoadTexture("../Images/dirt.png");
	grass = Texture::LoadTexture("../Images/grass.png");
	water = Texture::LoadTexture("../Images/water.png");
	white = Texture::LoadTexture("../Images/white.png");
	black = Texture::LoadTexture("../Images/black.png");
	Graph g(Game::rows, Game::cols, Game::seed);
	auto lvl1 = g.exportMtr;
	LoadMaze(lvl1);
	graph = g;
	path_src.x = path_src.y = 0;
	path_src.w = Game::original_w;
	path_src.h = Game::original_h;
	path_dest.w = Game::block_w;
	path_dest.h = Game::block_h;

	hor_wall_src.x = hor_wall_src.y = 0;
	hor_wall_src.w = Game::original_w;
	hor_wall_src.h = Game::wall_thickness;
	hor_wall_dest.w = Game::block_w;
	hor_wall_dest.h = Game::wall_thickness;

	vert_wall_src.x = vert_wall_src.y = 0;
	vert_wall_src.w = Game::wall_thickness;
	vert_wall_src.h = Game::original_h;
	vert_wall_dest.w = Game::wall_thickness;
	vert_wall_dest.h = Game::block_h;

	small_wall_src.x = small_wall_src.y = 0;
	small_wall_src.w = Game::wall_thickness;
	small_wall_src.h = Game::wall_thickness;
	small_wall_dest.w = Game::wall_thickness;
	small_wall_dest.h = Game::wall_thickness;
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
	Wall * wall;
	for(int i = 0; i < game_Maze.size(); i++){
		for(int j = 0; j < game_Maze[0].size(); j++){
			type = game_Maze[i][j];
			if(i % 2 == 0 and j % 2 == 0){
				path_dest.y = Game::menu + (i / 2) * (Game::block_h + Game::wall_thickness);
				path_dest.x = (j / 2) * (Game::block_w + Game::wall_thickness);
				game_Maze[i][j] = 0;
				Texture::Draw(water, path_src, path_dest);
			}
			else if(i % 2 == 1 and j % 2 == 0){
				hor_wall_dest.y = Game::menu + (i / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h;
				hor_wall_dest.x = (j / 2) * (Game::block_w + Game::wall_thickness);
				if(type == 0){
					game_Maze[i][j] = 0;
					Texture::Draw(water, hor_wall_src, hor_wall_dest);
				}
				else{
					if(!made){
						wall = new Wall(hor_wall_src, hor_wall_dest);
						Game::entities->Add(wall);
					}
					game_Maze[i][j] = 1;
					Texture::Draw(black, hor_wall_src, hor_wall_dest);
				}
			}
			else if(i % 2 == 0 and j % 2 == 1){
				vert_wall_dest.y = Game::menu + (i / 2) * (Game::block_h + Game::wall_thickness);
				vert_wall_dest.x = (j / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w;
				if(type == 0){
					game_Maze[i][j] = 0;
					Texture::Draw(water, vert_wall_src, vert_wall_dest);
				}
				else{
					if(!made){
						wall = new Wall(vert_wall_src, vert_wall_dest);
						Game::entities->Add(wall);
					}
					game_Maze[i][j] = 1;
					Texture::Draw(black, vert_wall_src, vert_wall_dest);
				}
			}
			else{
				small_wall_dest.y = Game::menu + (i / 2) * (Game::block_h + Game::wall_thickness) + Game::block_h;
				small_wall_dest.x = (j / 2) * (Game::block_w + Game::wall_thickness) + Game::block_w;
				int neighbor_walls = 0;
				if(game_Maze[i+1][j] == 1){
					neighbor_walls ++;
				}
				if(game_Maze[i-1][j] == 1){
					neighbor_walls ++;
				}
				if(game_Maze[i][j+1] == 1){
					neighbor_walls ++;
				}
				if(game_Maze[i][j-1] == 1){
					neighbor_walls ++;
				}
				if(neighbor_walls >= 0){
					if(!made){
						wall = new Wall(small_wall_src, small_wall_dest);
						Game::entities->Add(wall);
					}
					game_Maze[i][j] = 1;
					Texture::Draw(black, small_wall_src, small_wall_dest);
				}
				else{
					game_Maze[i][j] = 0;
					Texture::Draw(water, small_wall_src, small_wall_dest);
				}
			}
		}
	}
	if( !made ) made = true;
}