#include <iostream>
#include <vector>

//#define DEBUGME 1

using std::vector;
using std::pair;

void print(vector<vector<int>> &adj) {
    std::cout << "verticles: " << std::endl;
    
    for (size_t idx_1 = 0; idx_1 < adj.size(); idx_1++) {
        std::cout << idx_1 << " : ";
        for (size_t idx_2 = 0; idx_2 < adj[idx_1].size(); idx_2++) {
            std::cout << adj[idx_1][idx_2] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print(std::vector<size_t> history) {
    std::cout << "history: " << std::endl;
    for (size_t idx = 0; idx < history.size(); idx++) {
        std::cout << history[idx] << " ";
    }
    std::cout << std::endl;
}

void print(std::vector<bool> vec, std::string name) {
    std::cout << name <<": " << std::endl;
    for (size_t idx = 0; idx < vec.size(); idx++) {
        std::cout << vec[idx] << " ";
    }
    std::cout << std::endl;
}


void acyclic(vector<vector<int> > &adj) {
    std::vector<size_t> history(adj.size(), 0);
    std::vector<bool> sink(adj.size(), false);
    std::vector<bool> visited(adj.size(), false);
    
    std::vector<size_t> linear;
    
    size_t verticles_left = adj.size();
    long long history_idx = -1;
    size_t visited_idx = 0;
#ifdef DEBUGME
    print(adj);
#endif
    
    while(verticles_left > 0) {
#ifdef DEBUGME
        print(history);
        print(sink, "sink");
        print(visited, "visited");
        std::cout << std::endl;
#endif
        
        
        size_t current_idx;
        if (history_idx == -1) {
            for (visited_idx; visited[visited_idx] != false; visited_idx++) {}
            current_idx = visited_idx;
        } else {
            current_idx = history[history_idx];
        }
        
        
        bool is_sink = false;
        
        while(is_sink == false) {
            if (history_idx < 0 || current_idx != history[history_idx]) {
                history_idx++;
            }
            history[history_idx] = current_idx;
            visited[current_idx] = true;
            
#ifdef DEBUGME
            print(history);
            print(sink, "sink");
            print(visited, "visited");
            std::cout << std::endl;
#endif
            
            
            
            
            for(size_t idx = 0; idx < adj[current_idx].size(); idx++) {
                size_t child_idx = adj[current_idx][idx];
                if (sink[child_idx] != true) {
                    if (visited[child_idx] == true) {
                        return;
                    }
                    current_idx = child_idx;
                    break;
                }
            }
            
            if (current_idx == history[history_idx]) {
                sink[current_idx] = true;
                history_idx--;
                verticles_left--;
                is_sink = true;
                
                linear.push_back(current_idx + 1);
            }
#ifdef DEBUGME
            print(sink, "sink");
            std::cout << std::endl;
#endif
            
        }
    }
    
    for(long long idx = linear.size() - 1; idx >= 0; idx--) {
        std::cout << linear[idx] << " ";
    }
    
    
    //return 0;
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
    acyclic(adj);
    //std::cout << acyclic(adj);
}
