/*input
0 17 40 35 53 38 56 59 22 
17 0 53 48 66 51 69 72 35 
40 53 0 41 15 6 18 21 36 
35 48 41 0 54 39 57 60 31 
53 66 15 54 0 19 3 14 49 
38 51 6 39 19 0 22 25 34 
56 69 18 57 3 22 0 17 52 
59 72 21 60 14 25 17 0 55 
22 35 36 31 49 34 52 55 0 
*/
#include <algorithm>
#include "includes.hpp"
int start = 0, last = 8, s = 9;
vector<vector<int>> adj(s, vector<int>(s, 0));
vector<vector<int>> mst_adj(s, vector<int>(0));
vector<int> contains_end(s);
vector<int> walk;
vector<int> path;
vector<bool> vis(s);


bool comp(pair<int, int> &a, pair<int, int> &b) {
	return adj[a.first][a.second] < adj[b.first][b.second];
}

vector<int> parent, size;
void make_set(int n){
	parent.assign(n, 0);
	size.assign(n, 1);
	for(int i=0;i<n;i++) parent[i] = i;
}
int find_set(int v) { 
	if (v == parent[v]) return v; 
	return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
	a = find_set(a); b = find_set(b);
	if (a != b) { if (size[a] < size[b]) swap(a, b); parent[b] = a; size[a] += size[b];}
}
int dfs_init(int vertex, int last){
	vis[vertex] = 1;
	if(vertex == last){
		contains_end[vertex] = 1;
		return 1;
	}
	int ans = 0;
	for(auto u: mst_adj[vertex]){
		if(!vis[u]){
			ans = max(dfs_init(u, last), ans);
		}
	}
	contains_end[vertex] = ans;
	return ans;
}
void dfs(int vertex, int last){
	vis[vertex] = 1;
	walk.push_back(vertex);
	int left = -1;
	for(auto u:mst_adj[vertex]){
		if(contains_end[u] == 0 and vis[u] == 0){
			dfs(u, last);
		}
		else if(!vis[u]) left = u;
	}
	if(left != -1) dfs(left, last);
}
vector<int> tsp(vector<vector<int>> adj_param){
	mst_adj.assign(s, vector<int>(0));
	contains_end.assign(s, 0);
	vis.assign(s, 0);
	walk.assign(0, 0);
	path.assign(0, 0);
	adj = adj_param;
	vector<pair<int, int>> edges;
	for(int i=0;i<s;i++){
		for(int j=0;j<s;j++){
			if(i < j){
				edges.push_back({i, j});
			}
		}
	}
	make_set(s);
	sort(edges.begin(), edges.end(), comp);
	for(auto edge:edges){
		if(find_set(edge.first) != find_set(edge.second)){
			mst_adj[edge.first].push_back(edge.second);
			mst_adj[edge.second].push_back(edge.first);
			union_sets(edge.first, edge.second);
		}
	}
	// for(auto u:mst_adj){
	// 	for(auto x:u){
	// 		cout<<x<<" ";
	// 	}
	// 	cout<<endl;
	// }
	dfs_init(start, last);
	vis.assign(s, 0);
	dfs(start, last);
	for(auto u:walk){
		if(u != last) path.push_back(u);
	}
	path.push_back(last);
	return path;
}