#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<int>> Adj;
typedef long long Len;
typedef priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>> Queue;

typedef std::pair< std::pair<Len, Len>, std::pair<Len, Len> > Line;

const Len _INFINITY = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<Len> distance_;
    //vector<int> workset_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;
    //std::map<int, Len> cache;
    
    int source;
    int target;
public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
    : n_(n), adj_(adj), cost_(cost), distance_(n_, _INFINITY),/*cache(),*/ xy_(xy)
    { /*workset_.reserve(n);*/ }
    
    // See the description of this method in the starter for friend_suggestion
    void clear() {
        //        for (int i = 0; i < workset_.size(); ++i) {
        //            const int v = workset_[i];
        //            distance_[v]  = _INFINITY;
        //        }
        distance_ = vector<Len>(n_, _INFINITY);
        //workset_.clear();
        source = target = -1;
        //        cache.clear();
    }
    
    inline Len potencial(const int point) {
        //        Len result = -1;
        //
        //        if (cache[side].find(point) != cache[side].end()) {
        //            result = cache[side][point];
        //        } else {
        //            const std::pair<Len,Len> point_xy = xy_[point];
        //            const std::pair<Len,Len> target_xy = xy_[ (side == 0) ? target : source ];
        //            result = sqrt( pow(point_xy.first - target_xy.first, 2) + pow(point_xy.second - target_xy.second, 2) );
        //            cache[side][point] = result;
        //        }
        //
        //        return result;
        
        const std::pair<Len,Len> point_xy = xy_[point];
        const std::pair<Len,Len> target_xy = xy_[target];
        return sqrt( pow(point_xy.first - target_xy.first, 2) + pow(point_xy.second - target_xy.second, 2) );
    }
    
    // See the description of this method in the starter for friend_suggestion
    inline void visit(Queue& q, const int v) {
        const Len dist_v = distance_[v];
        const size_t count = adj_[v].size();
        
        for(int idx = 0; idx < count; idx++) {
            const int u = adj_[v][idx];
            const int cost_u = cost_[v][idx];
            const Len dist_u = dist_v + cost_u;
            
            if (distance_[u] > dist_u) {
                //                if (distance_[u] == _INFINITY /*&&  distance_[1][u] == _INFINITY*/) {
                //                    workset_.push_back(u);
                //                }
                
                distance_[u] = dist_u;
                
                //  if (stop_discovering == false) {
                const Len potencialed_dist = dist_u + potencial(u);
                const pair<Len, int> p(potencialed_dist, u);
                q.push(p);
                //}
            }
        }
        
        
    }
    
    inline int get_next_v(Queue &queue) {
        const int v = queue.top().second;
        queue.pop();
        return v;
    }
    
    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        if (s == t) return 0;
        clear();
        
        Queue q;
        source = s;
        target = t;
        distance_[s] = 0;
        //workset_.push_back(s);
        //workset_.push_back(t);
        visit(q, s);
        // visit(q, 1, t, distance_[1][t]);
        
        // int side = 0;//1;
        
        while (q.size()) {// || q[1].size()) {
            //side = !side;
            if (q.size() == 0) return -1;
            
            const int v = get_next_v(q);
            visit(q, v);
            
            if (distance_[t] < _INFINITY) {
                return distance_[t];
            }
            
            
            
            //            if (visited_[!side][v]) {
            //                best = min(best, distance_[side][v] + distance_[!side][v]);
            //                stop_discovering = true;
            //            }
        }
        return -1;
        //return best < _INFINITY ? best : -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(n);
    Adj cost(n);
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u-1].push_back(v-1);
        cost[u-1].push_back(c);
        //        adj[1][v-1].push_back(u-1);
        //        cost[1][v-1].push_back(c);
    }
    AStar astar(n, adj, cost, xy);
    
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
