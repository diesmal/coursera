#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
    
    vector<int> lenghts = vector<int>(adj.size(), -1);
    int s = 0;
    lenghts[s] = 0;
    
    queue<int> v_queue;
    v_queue.push(s);
    
    while (v_queue.empty() == false) {
        int current = v_queue.front();
        int current_lenght = lenghts[current];
        v_queue.pop();
        
        for (int idx = 0; idx < adj[current].size(); idx++) {
            int connection = adj[current][idx];
            if (lenghts[connection] == -1) {
                lenghts[connection] =  current_lenght + 1;
                v_queue.push(connection);
            } else {
                if (current_lenght % 2 == 0 && lenghts[connection] % 2 == 0) {
                    return 0;
                }
                if (current_lenght % 2 != 0 && lenghts[connection] % 2 != 0) {
                    return 0;
                }
            }
        }
    }
    
    for (int idx = 0; idx < lenghts.size(); idx++) {
        if (lenghts[idx] < 0) {
            return 0;
        }
    }
    
    
    //write your code here
    return 1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << bipartite(adj);
}
