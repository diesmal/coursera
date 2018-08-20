#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <iostream>

using namespace std;
typedef vector<vector<vector<int>>> Adj;

typedef long long Len;

typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    
    vector<int> workset_;
    vector<vector<bool>> visited_;
    
    bool stop_discovering;
public:
    Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(2, vector<bool>(n, false))
    { workset_.reserve(n); }
    
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[0][v] = visited_[1][v] = false;
        }
        workset_.clear();
        stop_discovering = false;
    }
    
    
    inline void visit(Queue& q, int side, int v, Len dist) {
        for(int idx = 0; idx <  cost_[side][v].size(); idx++) {
            const int cost_v = cost_[side][v][idx];
            const int adj_v = adj_[side][v][idx];
            const Len dist_to_v = cost_v + dist;
            
            if (distance_[side][adj_v] > dist_to_v) {
                
                if (distance_[0][adj_v] == INFINITY &&  distance_[1][adj_v] == INFINITY) {
                    workset_.push_back(adj_v);
                }
                
                distance_[side][adj_v] = dist_to_v;
                if (stop_discovering == false) {
                    pair<Len, int> p(dist_to_v, adj_v);
                    q[side].push(p);
                }
            }
        }
        
        visited_[side][v] = true;
    }
    
    
    Len query(int s, int t) {
        if (s == t) return 0;
        clear();
        Queue q(2);
        distance_[0][s] = 0;
        distance_[1][t] = 0;
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        workset_.push_back(s);
        workset_.push_back(t);
        
        int n = 1;
        Len best = INFINITY;
        
        
        while (q[0].size() || q[1].size()) {
            n = !n;
            if (q[n].size() == 0) continue;
            
            const pair<Len, int> p = q[n].top(); q[n].pop();
            const Len dist = p.first;
            const int v = p.second;
            
            if (dist >= best) continue;
            if (stop_discovering && ((dist + distance_[!n][v]) > best)) continue;
            
            visit(q, n, v, dist);
            
            if (visited_[!n][v]) {
                best = min(best, (dist + distance_[!n][v]));
                stop_discovering = true;
            }
        }
        
        return best < INFINITY ? best : -1;
    }
};

int main() {
    srand((unsigned)time(NULL));
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<Len,Len>> xy(n);
    
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    vector<vector<int>> incoming(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
        
        incoming[v-1].push_back(u-1);
    }
    
    Bidijkstra bidij(n, adj, cost);
    
    std::cout << "Ready\n";
    
    int t;
    std::cin >> t;
    for (int i=0; i<t; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << bidij.query(u-1, v-1) << std::endl;
    }
}
