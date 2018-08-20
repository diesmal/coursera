#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool foundWay(vector<vector<int> > &adj, int from, int to, vector<bool> &visited) {
    
    
    
    visited[from] = true;
    
    if (visited[to] == true) {
        return true;
    }
    
    visited[from] = true;
    
    for (size_t i = 0; i < adj[from].size(); i++) {
        int next = adj[from][i];
        if (visited[next] == false) {
            if (foundWay(adj, next, to, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

int reach(vector<vector<int> > &adj, int x, int y) {
    vector<bool> visited(adj.size(), false);
    
    return foundWay(adj, x, y, visited);
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
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
