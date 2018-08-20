#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<vector<bool>> visited_;
    
    bool stop_discovering;
public:
    Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(2, vector<bool>(n, false))
    { workset_.reserve(n); }
    
    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[0][v] = visited_[1][v] = false;
        }
        workset_.clear();
        stop_discovering = false;
    }
    
    //    Len shortestDistance() {
    //        Len s_distance = INFINITY;
    //        for (int i = 0; i < workset_.size(); ++i) {
    //            int v = workset_[i];
    //            if (distance_[0][v] != INFINITY && distance_[1][v] != INFINITY) {
    //                s_distance = min(s_distance, (distance_[0][v] + distance_[1][v]));
    //            }
    //        }
    //        return s_distance;
    //    }
    
    // Processes visit of either forward or backward search
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
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
    
    
    
    // Returns the distance from s to t in the graph.
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
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }
    
    Bidijkstra bidij(n, adj, cost);
    
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u-1, v-1));
    }
}
