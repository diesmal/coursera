#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::priority_queue;

struct Point {
    int x;
    int y;
};

struct Relation {
    Point point1;
    Point point2;
    double lenght;
    size_t number_1;
    size_t number_2;
};

class Compare
{
public:
    bool operator() (Relation* l, Relation* r){
        return l->lenght > r->lenght;
    }
};


inline double lenght(const Point &p1, const Point &p2) {
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
}


double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0.;
    size_t points_count = x.size();
    if (points_count < 2)
        return result;
    
    vector< vector<Relation *> > realations(points_count);
    
    for (size_t i = 0; i < points_count; i++) {
        for (size_t j = 0; j < points_count; j++) {
            Relation *r = new Relation;
            r->number_1 = i;
            r->number_2 = j;
            r->point1.x = x[i];
            r->point1.y = y[i];
            r->point2.x = x[j];
            r->point2.y = y[j];
            r->lenght = lenght(r->point1, r->point2);
            realations[i].push_back(r);
        }
    }
    
    priority_queue<Relation *, vector<Relation *>, Compare> queue;
    vector<double> connect_lenghts(points_count, INFINITY);
    
    connect_lenghts[0] = 0;
    size_t last_connection = 0;
    
    for(int counter = 0; counter < points_count; counter++) {
        for(int idx = 0; idx < points_count; idx++) {
            if (connect_lenghts[idx] == INFINITY) {
                queue.push(realations[last_connection][idx]);
            }
        }
        
        Relation *r = NULL;
        while (queue.size() > 0 && r == NULL) {
            r = queue.top();
            queue.pop();
            if (connect_lenghts[r->number_1] != INFINITY &&
                connect_lenghts[r->number_2] != INFINITY) {
                r = NULL;
            }
        }
        if (r != NULL) {
            size_t number = (connect_lenghts[r->number_2] == INFINITY) ? r->number_2 : r->number_1;
            connect_lenghts[number] = r->lenght;
            last_connection = number;
        }
    }
    
    
    //Result
    for (size_t idx = 1; idx < points_count; idx++) {
        //  std::cout << connect_lenghts[idx] << " ";
        result += connect_lenghts[idx];
    }
    //std::cout << std::endl;
    
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
