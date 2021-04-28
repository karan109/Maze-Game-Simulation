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
	vector<int> getDistances(int src, vector<int> & dests); // Given a source and vector of destinations, returns distances to each element of dests as a vector
	int distance (int src, int des);
private:
	int height, width; // Number of rows and columns of nodes grid
	vector<vector<int>> adj; // Adjacency list of final graph
	vector<pair<int, int>> edges; // Edge list of final graph
	int n; // Total number of nodes (height * width)
	vector<vector<int>> MST(string algo); // Returns adjacency list of MST and sets edges variable to edge list
	void dfs(int vertex, vector<pair<int, int>> & result, int & count, vector<bool> & vis);
	void removeLeaves(vector<vector<int>> & final_adj, bool remove); // Sets adj variable to adjecency list and adds some edges to "edges" depending on the bool argument
	bool getPathdfs(int vertex, vector<bool> & vis, vector<int> & result, int dest);
	void getPathbfs(int src, vector<bool> & vis, vector<int> & result, int dest);
};