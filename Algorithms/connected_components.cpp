#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void visit_all_connections(vector<vector<int> > &adj, int point,  vector<bool> &visited) {
    visited[point] = true;
    for (int i = 0; i < adj[point].size(); i++) {
        int next = adj[point][i];
        if (visited[next] == false) {
            visit_all_connections(adj, next, visited);
        }
    }
}

int number_of_components(vector<vector<int> > &adj) {
    int res = 0;
    vector<bool> visited(adj.size(), false);
    
    
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == false) {
            visit_all_connections(adj, i, visited);
            res++;
        }
    }
    
    
    
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_components(adj);
}


