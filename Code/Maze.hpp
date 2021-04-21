#pragma once

#include "includes.hpp"
#include "Graph.hpp"
class Maze{
public:
	Maze();
	~Maze();
	void LoadMaze(vector<vector<int>> arr);
	void DrawMaze(); // Draw maze
	bool made;
	vector<vector<int>> game_Maze;
	Graph graph;
private:
	SDL_Rect path_src, path_dest, hor_wall_src, hor_wall_dest, vert_wall_src, vert_wall_dest;
	SDL_Rect small_wall_src, small_wall_dest;
	SDL_Texture * dirt, * grass, * water, * white, * black;
};