#pragma once

#include "includes.hpp"

class Graph{
public:
	Graph(int height, int width, int seed);
	void generate();
	vector<vector<int>> exportMtr;
private:
	int height, width;
	vector<vector<int>> adj;
	vector<pair<int, int>> edges;
	int n;
	vector<vector<int>> MST(string algo);
	void dfs(int vertex, vector<pair<int, int>> & result, int & count, vector<bool> & vis);
	void removeLeaves(vector<vector<int>> & final_adj);
};