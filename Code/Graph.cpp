#include "Graph.hpp"
#include "Game.hpp"

Graph::Graph(int heightMtr, int widthMtr, int seed){
	srand(seed);
	// srand(time(0));

	height = heightMtr;
	width = widthMtr;
	n = height * width;
	adj.assign(n, vector<int>(0));
	exportMtr.assign(height * 2 - 1, vector<int>(width * 2 - 1, 1));
	for(int i=0; i < exportMtr.size(); i++){
		for(int j = 0; j < exportMtr[0].size(); j++){
			if(i % 2 == 0 and j % 2 == 0){
				exportMtr[i][j] = 0;
			}
		}
	}
	auto final_adj = MST("dfs");
	removeLeaves(final_adj, Game::no_trap);
	for(auto u : edges){
		int p1 = u.first, p2 = u.second;
		int r1, c1, r2, c2;
		r1 = p1 / width;
		r2 = p2 / width;
		c1 = p1 % width;
		c2 = p2 % width;
		if(r1-r2 == 1 and c1 == c2){
			exportMtr[r1 * 2 - 1][c1 * 2] = 0;
		}
		else if(r1-r2 == -1 and c1 == c2){
			exportMtr[r1 * 2 + 1][c1 * 2] = 0;
		}
		if(c1-c2 == 1 and r1 == r2){
			exportMtr[r1 * 2][c1 * 2 - 1] = 0;
		}
		if(c1-c2 == -1 and r1 == r2){
			exportMtr[r1 * 2][c1 * 2 + 1] = 0;
		}
	}
}
void Graph::dfs(int vertex, vector<pair<int, int>> & result, int & count, vector<bool> & vis){
	vis[vertex] = 1;
	count ++ ;
	if(count == n){
		return;
	}
	vector<pair<int, int>> non_visited;
	for(auto neighbor : adj[vertex]){
		if(!vis[neighbor]) non_visited.push_back({0, neighbor});
	}
	if(non_visited.size() == 0) return;
	for(auto & neighbor : non_visited){
		neighbor.first = rand();
	}
	sort(non_visited.begin(), non_visited.end());
	for(auto & neighbor : non_visited){
		if(!vis[neighbor.second]){
			result.push_back({neighbor.second, vertex});
			dfs(neighbor.second, result, count, vis);
		}
	}
}

void Graph::removeLeaves(vector<vector<int>> & final_adj, bool remove){
	if(remove){
		set<int> leaves;
		for(int i=0;i<n;i++){
			if(final_adj[i].size() == 1){
				leaves.insert(i);
			}
		}
		while( !leaves.empty() ){
			int leaf = * leaves.begin();
			int current_neighbor = final_adj[leaf][0];
			for(auto neighbor : adj[leaf]){
				if(neighbor == current_neighbor) continue;
				final_adj[neighbor].push_back(leaf);
				final_adj[leaf].push_back(neighbor);
				edges.push_back({neighbor, leaf});
				if(final_adj[neighbor].size() == 2){
					leaves.erase(neighbor);
				}
				break;
			}
			leaves.erase(leaf);
		}
	}
	adj = final_adj;
}

vector<vector<int>> Graph::MST(string algo = "prim"){
	if(algo == "prim"){
		vector<bool> vis(n, 0);
		map<pair<int, int>, int> wall_to_ind;
		map<int, pair<int, int>> ind_to_wall;
		set<int> initial_edges;
		set<int> taken;
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				if(i+1 < height){
					adj[i * width + j].push_back((i+1) * width + j);
					adj[(i+1) * width + j].push_back(i * width + j);
					pair<int, int> wall = {i * width + j, (i+1) * width + j};
					pair<int, int> wall_copy = {(i+1) * width + j, i * width + j};
					if(wall_to_ind.find(wall) == wall_to_ind.end()){
						int possible_ind;
						while(true){
							possible_ind = rand();
							if(taken.find(possible_ind) == taken.end()){
								taken.insert(possible_ind);
								break;
							}
						}
						wall_to_ind[wall] = possible_ind;
						wall_to_ind[wall_copy] = possible_ind;
						ind_to_wall[possible_ind] = wall;
					}
				}
				if(j+1 < width){
					adj[i * width + j].push_back(i * width + j + 1);
					adj[i * width + j + 1].push_back(i * width + j);
					pair<int, int> wall = {i * width + j, i * width + j + 1};
					pair<int, int> wall_copy = {i * width + j + 1, i * width + j};
					if(wall_to_ind.find(wall) == wall_to_ind.end()){
						int possible_ind;
						while(true){
							possible_ind = rand();
							if(taken.find(possible_ind) == taken.end()){
								taken.insert(possible_ind);
								break;
							}
						}
						wall_to_ind[wall] = possible_ind;
						wall_to_ind[wall_copy] = possible_ind;
						ind_to_wall[possible_ind] = wall;
					}
				}
			}
		}
		int start = 0;
		vis[start] = true;
		for(auto neighbor : adj[start]){
			initial_edges.insert(wall_to_ind[{start, neighbor}]);
		}
		while( ! initial_edges.empty() ){
			auto candidate = initial_edges.begin();
			auto wall = ind_to_wall[ * candidate];
			if(vis[wall.first] == false or vis[wall.second] == false){
				int new_vertex = -1;
				if(vis[wall.first] == false) new_vertex = wall.first;
				else new_vertex = wall.second;
				vis[new_vertex] = true;
				for(auto neighbor : adj[new_vertex]){
					if(! vis[neighbor]){
						initial_edges.insert(wall_to_ind[{neighbor, new_vertex}]);
					}
				}
				edges.push_back({wall});
			}
			initial_edges.erase(candidate);
		}
		vector<vector<int>> final_adj(n, vector<int>(0));
		for(auto edge : edges){
			final_adj[edge.first].push_back(edge.second);
			final_adj[edge.second].push_back(edge.first);
		}
		return final_adj;
	}
	else if(algo == "dfs"){
		vector<bool> vis(n, 0);
		int count = 0;
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				if(i+1 < height){
					adj[i * width + j].push_back((i+1) * width + j);
					adj[(i+1) * width + j].push_back(i * width + j);
				}
				if(j+1 < width){
					adj[i * width + j].push_back(i * width + j + 1);
					adj[i * width + j + 1].push_back(i * width + j);
				}
			}
		}
		dfs(0, edges, count, vis);
		vector<vector<int>> final_adj(n, vector<int>(0));
		for(auto edge : edges){
			final_adj[edge.first].push_back(edge.second);
			final_adj[edge.second].push_back(edge.first);
		}
		return final_adj;
	}
	else return {{}};
}
vector<int> Graph::getPath(int src, int dest){
	vector<bool> vis(n, 0);
	vector<int> result;
	// getPathdfs(src, vis, result, dest);
	getPathbfs(src, vis, result, dest);
	return result;
}
bool Graph::getPathdfs(int vertex, vector<bool> & vis, vector<int> & result, int dest){
	vis[vertex] = 1;
	result.push_back(vertex);
	if(vertex == dest){
		return true;
	}
	for(auto neighbor : adj[vertex]){
		if(!vis[neighbor]){
			if(getPathdfs(neighbor, vis, result, dest)) return true;
		}
	}
	result.pop_back();
	return false;
}
void Graph::getPathbfs(int src, vector<bool> & vis, vector<int> & result, int dest){
	queue<int> q;
	q.push(src);
	vis[src] = 1;
	vector<int> parent(n);
	parent[src] = -1;
	while( !q.empty() ){
		int front = q.front();
		q.pop();
		for(auto neighbor : adj[front]){
			if( !vis[neighbor] ){
				q.push(neighbor);
				parent[neighbor] = front;
				vis[neighbor] = 1;
				if(neighbor == dest) break;
			}
		}
	}
	int vertex = dest;
	while(vertex != -1){
		result.push_back(vertex);
		vertex = parent[vertex];
	}
	reverse(result.begin(), result.end());
}
vector<int> Graph::getDistances(int src, vector<int> & dests){
	vector<bool> vis(n, 0);
	queue<int> q;
	q.push(src);
	vis[src] = 1;
	vector<int> dist(n);
	dist[src] = 0;
	while( !q.empty() ){
		int front = q.front();
		q.pop();
		for(auto neighbor : adj[front]){
			if( !vis[neighbor] ){
				q.push(neighbor);
				dist[neighbor] = dist[front] + 1;
				vis[neighbor] = 1;
			}
		}
	}
	vector<int> result;
	for(auto u : dests){
		result.push_back(dist[u]);
	}
	return result;
}
vector<vector<int>> Graph::getAdjMtr(vector<int> points){
	vector<vector<int>> result;
	for(auto u : points){
		result.push_back(Graph::getDistances(u, points));
	}
	return result;
}
vector<vector<int>> Graph::permute(int n){
	if(n == 1) return {{1}};
	auto small = permute(n-1);
	vector<vector<int>> result;
	for(auto u : small){
		for(int i=0;i<n;i++){
			vector<int> temp(n);
			temp[i] = n;
			int ct = 0;
			for(int j=0;j<i;j++){
				temp[j] = u[ct++];
			}
			for(int j=i+1;j<n;j++){
				temp[j] = u[ct++];
			}
			result.push_back(temp);
		}
	}
	return result;
}
int Graph::distance(int src, int des) {
	vector<int> v;
	v.push_back(des);
	vector<int> ans = getDistances(src, v);
	if (ans.empty()) return -1;
	else return ans[0];
}