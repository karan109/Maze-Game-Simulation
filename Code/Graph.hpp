#pragma once

#include "includes.hpp"

class Graph{
public:
	Graph(int height, int width, int seed);
	Graph(){}
	void generate();
	vector<vector<int>> exportMtr;
	vector<int> getPath(int src, int dest);
	vector<vector<int>> getAdjMtr(vector<int> points);
	vector<vector<int>> permute(int n);
private:
	int height, width;
	vector<vector<int>> adj;
	vector<pair<int, int>> edges;
	int n;
	vector<vector<int>> MST(string algo);
	void dfs(int vertex, vector<pair<int, int>> & result, int & count, vector<bool> & vis);
	void removeLeaves(vector<vector<int>> & final_adj, bool remove);
	bool getPathdfs(int vertex, vector<bool> & vis, vector<int> & result, int dest);
	void getPathbfs(int src, vector<bool> & vis, vector<int> & result, int dest);
	vector<int> getDistances(int src, vector<int> & dests);
};