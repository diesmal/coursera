#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

using std::vector;
using std::pair;
using std::priority_queue;
using std::map;

struct Relation {
    int point1;
    int point2;
    double lenght;
};

class Compare {
public:
    bool operator() (Relation* l, Relation* r){
        return l->lenght > r->lenght;
    }
};

inline double lenght(const int &x1, const int &y1, const int &x2, const int &y2) {
    return sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
}

double clustering(vector<int> x, vector<int> y, int k) {
    
    size_t N = x.size();
    
    bool calculated[N][N];
    for (int x = 0; x < N; x++)
        for(int y = 0; y < N; y++)
            calculated[x][y] = (x == y);
    
    int point_segment[N];
    map<int, vector<int>> segments;
    priority_queue<Relation *, vector<Relation *>, Compare> queue;
    
    for (int p1 = 0; p1 < N; p1++) {
        for(int p2 = 0; p2 < N; p2++) {
            if (calculated[p1][p2] == false) {
                calculated[p1][p2] = true;
                calculated[p2][p1] = true;
                
                Relation *r = new Relation;
                r->point1 = p1;
                r->point2 = p2;
                r->lenght = lenght(x[p1], y[p1], x[p2], y[p2]);
                
                queue.push(r);
            }
        }
        point_segment[p1] = p1;
        segments[p1].push_back(p1);
    }
    
    while (segments.size() >= k) {
        Relation *r = queue.top(); queue.pop();
        int s1 = point_segment[r->point1];
        int s2 = point_segment[r->point2];
        if (s1 == s2) continue;
        
        if (segments.size() == k) {
            return r->lenght;
        }
        
        for(int idx = 0; idx < segments[s2].size(); idx++) {
            int point = segments[s2][idx];
            segments[s1].push_back(point);
            point_segment[point] = s1;
        }
        segments.erase(s2);
    }
    
    return -1.;
}

int main() {
    size_t n;
    int k;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
