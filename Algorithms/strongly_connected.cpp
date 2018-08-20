#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
 
 void print(vector<int> &path) {
 std::cout << "PATH: ";
 for (size_t idx = 0; idx < path.size(); idx++) {
 std::cout << path[idx] << " ";
 }
 std::cout << std::endl;
 }
 
 void print(vector<vector<int>> &adj) {
 std::cout << "verticles: " << std::endl;
 
 for (size_t idx_1 = 0; idx_1 < adj.size(); idx_1++) {
 std::cout << idx_1 << " : ";
 for (size_t idx_2 = 0; idx_2 < adj[idx_1].size(); idx_2++) {
 std::cout << adj[idx_1][idx_2] + 1 << " ";
 }
 std::cout << std::endl;
 }
 std::cout << std::endl;
 }
 
 /* */

void DFS(vector<vector<int> > &adj, int v, vector<bool> &visited, vector<int> &path) {
    visited[v] = true;
    for(size_t idx = 0; idx < adj[v].size(); idx++) {
        int w = adj[v][idx];
        if (visited[w] == false) {
            DFS(adj, w, visited, path);
        }
    }
    path.push_back(v);
}



vector<vector<int>> invert(vector<vector<int> > &adj) {
    vector<vector<int> > adj_inverted(adj.size(), vector<int>());
    for(int v = 0; v < adj.size(); v++) {
        for (int u = 0; u < adj[v].size(); u++) {
            int connected = adj[v][u];
            adj_inverted[connected].push_back(v);
        }
    }
    return adj_inverted;
}

int number_of_strongly_connected_components(vector<vector<int> > &adj) {
    int result = 0;
    
    vector<vector<int> > adj_i = invert(adj);
    //    std::cout << "ORIGIN: " << std::endl;
    //    print(adj);
    //    std::cout << "INVERTED: " << std::endl;
    //    print(adj_i);
    //    std::cout << std::endl;
    
    vector<bool> visited_i(adj.size(), false);
    for (int idx_i = 0; idx_i < visited_i.size(); idx_i++) {
        if (visited_i[idx_i] == false) {
            vector<int> path_i;
            DFS(adj_i, idx_i, visited_i, path_i);
            //            std::cout << "inverted: ";
            //            print(path_i);
            
            
            vector<bool> visited(adj.size(), false);
            for (long long idx = path_i.size() - 1; idx >= 0; idx--) {
                if (visited[path_i[idx]] == false) {
                    vector<int> path;
                    DFS(adj, path_i[idx], visited, path);
                    result++;
                    //                    std::cout << "origin: ";
                    //                    print(path);
                }
            }
            
        }
    }
    
    
    
    
    
    
    
    
    
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << number_of_strongly_connected_components(adj);
}
