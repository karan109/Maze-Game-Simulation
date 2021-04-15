#pragma once

#include "includes.hpp"

class Maze{
public:
	Maze();
	~Maze();
	void LoadMaze(vector<vector<int>> arr);
	void DrawMaze();
private:
	SDL_Rect path_src, path_dest, hor_wall_src, hor_wall_dest, vert_wall_src, vert_wall_dest;
	SDL_Rect small_wall_src, small_wall_dest;
	SDL_Texture * dirt, * grass, * water;
	vector<vector<int>> game_Maze;
};