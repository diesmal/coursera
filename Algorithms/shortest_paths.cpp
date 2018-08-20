#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

const long long INF = std::numeric_limits<long>::max();

void shortest_paths(vector<vector<long long> > &adj, vector<vector<long long> > &costs, long long s, vector<long long> &distance, vector<bool> &reachable, vector<bool> &shortest) {
    
    vector<long long> negative;
    
    distance[s] = 0;
    reachable[s] = true;
    
    size_t n = adj.size();
    
    for(size_t idx = 0; idx <= n; idx++) {
        for(size_t x = 0; x < adj.size(); x++) {
            if (reachable[x] == false) continue;
            long long from = x;
            for(size_t y = 0; y < adj[x].size(); y++) {
                long long to = adj[x][y];
                long long cost = costs[x][y];
                
                reachable[to] = true;
                if (distance[to] > distance[from] + cost) {
                    distance[to] = distance[from] + cost;
                    if (idx == n) {
                        negative.push_back(to);
                    }
                }
            }
        }
    }
    
    for (long long idx = 0; idx < negative.size(); idx++) {
        long long current = negative[idx];
        if (shortest[current]) {
            shortest[current] = false;
            for (long long x = 0; x < adj[current].size(); x++) {
                long long connection = adj[current][x];
                negative.push_back(connection);
            }
        }
    }
}

int main() {
    long long n, m, s;
    std::cin >> n >> m;
    vector<vector<long long> > adj(n, vector<long long>());
    vector<vector<long long> > cost(n, vector<long long>());
    for (long long i = 0; i < m; i++) {
        long long x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, INF);
    vector<bool> reachable(n, false);
    vector<bool> shortest(n, true);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (long long i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
