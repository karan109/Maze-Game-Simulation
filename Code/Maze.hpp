#pragma once

#include "includes.hpp"

class Maze{
public:
	Maze();
	~Maze();
	void LoadMaze(vector<vector<int>> arr);
	void DrawMaze();
private:
	SDL_Rect src, dest;
	SDL_Texture * dirt, * grass, * water;
	vector<vector<int>> game_Maze;
};