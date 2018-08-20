#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<int>> Adj;
typedef long long Len;
typedef priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>> Queue;

typedef std::pair< std::pair<Len, Len>, std::pair<Len, Len> > Line;

const Len _INFINITY = numeric_limits<Len>::max() / 4;

const int init_landmarks_count = 12;//60;

class AStar {
    int n_;
    Adj outgoing_adj;
    Adj incoming_adj;
    Adj cost_;
    vector<Len> distance_;
    
    int _target;
    
    
    // Landmarks stuff
    int real_landmarks_count;
    std::vector<std::vector<Len>> landmarks;
    
public:
    AStar(int n, Adj outgoing, Adj incoming, Adj cost, std::vector<std::pair<Len,Len>> xy)
    : n_(n), outgoing_adj(outgoing), incoming_adj(incoming), cost_(cost), distance_(n_, _INFINITY), landmarks(init_landmarks_count, vector<Len>(n_, _INFINITY))
    {}
    
#pragma mark - BASE
    
    void clear() {
        distance_ = vector<Len>(n_, _INFINITY);
        _target = -1;
    }
    
    inline Len potencial(const int point) {
        Len potencial = 0;
        //        for (int i = 0; i < real_landmarks_count; i++) {
        //            if (landmarks[i][point] != _INFINITY && landmarks[i][_target] != _INFINITY) {
        //                potencial = max(potencial, abs(landmarks[i][point] - landmarks[i][_target]));
        //            }
        //        }
        
        return potencial;
    }
    
    inline void visit(Queue& q, const int v) {
        const Len dist_v = distance_[v];
        const size_t count = outgoing_adj[v].size();
        
        for(int idx = 0; idx < count; idx++) {
            const int u = outgoing_adj[v][idx];
            const int cost_u = cost_[v][u];
            const Len dist_u = dist_v + cost_u;
            
            if (distance_[u] > dist_u) {
                distance_[u] = dist_u;
                
                const Len potencialed_dist = dist_u + potencial(u);
                const pair<Len, int> p(potencialed_dist, u);
                q.push(p);
                
            }
        }
    }
    
    Len query(int s, int t) {
        if (s == t) return 0;
        //        for (int i = 0; i < real_landmarks_count; i++) {
        //            if (landmarks[i][s] == 0) {
        //                return landmarks[i][t] < _INFINITY ? landmarks[i][t] : -1;
        //            }
        //        }
        
        clear();
        
        Queue q;
        _target = t;
        distance_[s] = 0;
        visit(q, s);
        
        while (q.size()) {
            if (q.size() == 0) return -1;
            
            const int v = q.top().second;
            q.pop();
            
            if (v == _target) {
                return distance_[_target];
            }
            
            visit(q, v);
        }
        
        return distance_[t] < _INFINITY ? distance_[t] : -1;
    }
    
    void preprocess() {
        preprocess_shortcuts();
        //  preprocess_landmarks();
    }
    
#pragma mark - PREPROCESS landmars
    inline void preprocess_landmarks_visit(Queue& q, const int v, const int landmark_num) {
        const Len dist_v = landmarks[landmark_num][v];
        const size_t count = outgoing_adj[v].size();
        
        for(int idx = 0; idx < count; idx++) {
            const int u = outgoing_adj[v][idx];
            const int cost_u = cost_[v][u];
            const Len dist_u = dist_v + cost_u;
            
            if (landmarks[landmark_num][u] > dist_u) {
                landmarks[landmark_num][u] = dist_u;
                const pair<Len, int> p(dist_u, u);
                q.push(p);
            }
        }
    }
    
    //    void print_landmarks() {
    //        for (int l = 0; l < real_landmarks_count; l++) {
    //            std::cout << l + 1 << " : ";
    //            for (int i = 0; i < n_; i++) {
    //                if (landmarks[l][i] == _INFINITY) {
    //                    std::cout << "INF ";
    //                } else {
    //                    std::cout << landmarks[l][i] << " ";
    //                }
    //            }
    //            std::cout << std::endl;
    //        }
    //    }
    
    inline bool isLandmarkProcessed(const int landmark, const vector<int> &added_landmarks) {
        for(int l = 0; l < added_landmarks.size(); l++) {
            if (added_landmarks[l] == landmark) {
                return true;
            }
        }
        return false;
    }
    
    void preprocess_landmarks() {
        Queue q;
        int landmark = 0;
        real_landmarks_count = init_landmarks_count;
        
        vector<int> added_landmarks = vector<int>();
        
        for (int i = 0; i < init_landmarks_count; i++) {
            
            if (isLandmarkProcessed(landmark, added_landmarks)) {
                for(int r = 0; r < n_; r++) {
                    landmark = rand() % n_;
                    if (isLandmarkProcessed(landmark, added_landmarks)) {
                        landmark = -1;
                    } else {
                        break;
                    }
                }
                if (landmark == -1) {
                    real_landmarks_count = (int)added_landmarks.size();
                    //                    print_landmarks();
                    return;
                }
            }
            
            added_landmarks.push_back(landmark);
            clear();
            Len maxDist = 0;
            landmarks[i][landmark] = 0;
            preprocess_landmarks_visit(q, landmark, i);
            while (q.size()) {
                const int v = q.top().second;
                q.pop();
                
                Len currentDist = 0;
                for (int a = 0; a <= i; a++) {
                    currentDist += landmarks[a][v];
                }
                if (maxDist < currentDist) {
                    if (outgoing_adj[v].size() > 0) {
                        maxDist = currentDist;
                        landmark = v;
                    }
                }
                
                preprocess_landmarks_visit(q, v, i);
            }
        }
    }
#pragma mark - PREPROCESS shortcuts
    
    inline void visit_shortcuts(Queue& q, const int v, const Len max_dist) {
        const Len dist_v = distance_[v];
        const size_t count = outgoing_adj[v].size();
        
        for(int idx = 0; idx < count; idx++) {
            const int u = outgoing_adj[v][idx];
            const int cost_u = cost_[v][u];
            const Len dist_u = dist_v + cost_u;
            
            if (dist_u > max_dist) continue;
            
            if (distance_[u] > dist_u) {
                distance_[u] = dist_u;
                const pair<Len, int> p(dist_u, u);
                q.push(p);
            }
        }
    }
    
    Len query_shortcuts(const int source, const int target, const int exclusion, const Len current_cost) {
        clear();
        
        Queue q;
        
        distance_[source] = 0;
        visit_shortcuts(q, source, current_cost);
        
        int max_edges = 5;
        
        while (q.size() && max_edges > 0) {
            if (q.size() == 0) return _INFINITY;
            
            const int v = q.top().second;
            q.pop();
            if (v == exclusion) continue;
            
            if (v == _target) {
                return distance_[_target];
            }
            
            visit_shortcuts(q, v, current_cost);
            max_edges--;
        }
        
        return distance_[target];
    }
    
    inline void add_shortcuts(const int v) {
        const int incoming_count = (int)incoming_adj[v].size();
        const int outgoing_count = (int)outgoing_adj[v].size();
        
        if (incoming_count == 0 || outgoing_count == 0) {
            return;
        }
        
        for (int i = 0; i < incoming_count; i++) {
            const int i_adj = incoming_adj[v][i];
            for (int o = 0; o < outgoing_count; o++) {
                const int o_adj = outgoing_adj[v][o];
                if (i_adj == o_adj) {
                    continue;
                }
                
                const Len current_dist = cost_[i_adj][v] + cost_[v][o_adj];
                const Len min_dist = query_shortcuts(i_adj, o_adj, v, current_dist);
                
                if (current_dist <= min_dist) {
                    if (cost_[i_adj][o_adj] == -1) {
                        outgoing_adj[i_adj].push_back(o_adj);
                        incoming_adj[o_adj].push_back(i_adj);
                        //std::cout << "adeded: " << i_adj << " " << o_adj << " cost: " << current_dist << std::endl;
                    }
                    cost_[i_adj][o_adj] = (int)current_dist;
                }
            }
        }
    }
    
    void preprocess_shortcuts() {
        const clock_t begin = clock();
        double elapsed_secs;
        int left = n_;
        do {
            add_shortcuts(rand() % n_);
            elapsed_secs = double(clock() - begin) / CLOCKS_PER_SEC;
            left--;
        } while (elapsed_secs < 7 && left > 0);
    }
    
};

int main() {
    srand((unsigned)time(NULL));
    
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<Len,Len>> xy(n);
    
    Adj outgoing(n);
    Adj incoming(n);
    Adj cost(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i){
        cost[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        outgoing[u-1].push_back(v-1);
        incoming[v-1].push_back(u-1);
        cost[u-1][v-1] = c;
    }
    AStar astar(n, outgoing, incoming, cost, xy);
    astar.preprocess();
    
    std::cout << "Ready\n" << std::flush;
    
    int t;
    std::cin >> t;
    for (int i=0; i<t; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << astar.query(u-1, v-1) << std::endl;
    }
}
