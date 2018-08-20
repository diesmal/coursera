#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

struct Vertex {
    int number;
    int waste;
    
    Vertex(int n, int w) {
        number = n;
        waste = w;
    }
};

class Compare
{
public:
    bool operator() (Vertex* l, Vertex* r){
        return l->waste > r->waste;
    }
};


int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &costs) {
    
    vector<int> waste(adj.size(), -1);
    
    for (int s = 0; s < waste.size(); s++) {
        if (waste[s] == -1) {
            waste[s] = 0;
            priority_queue<Vertex *, vector<Vertex *>, Compare> queue;
            queue.push(new Vertex(s, 0));
            int counter = 0;
            while (queue.size() > 0) {
                counter++;
                
                if (counter > waste.size()) {
                    return 1;
                }
                
                Vertex *current = queue.top();
                queue.pop();
                
                for(int idx = 0; idx < adj[current->number].size(); idx++) {
                    int connection = adj[current->number][idx];
                    int cost = current->waste + costs[current->number][idx];
                    if (waste[connection] == -1 || waste[connection] > cost) {
                        queue.push(new Vertex(connection, cost));
                        waste[connection] = cost;
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
