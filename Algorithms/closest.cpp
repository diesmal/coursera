#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

using std::vector;
using std::string;
using std::pair;
using std::min;

struct Point {
    long x;
    long y;
};

Point mp[2];
Point rp[2];

/// SORTING
int compare_x(const void* p1, const void* p2) {
    if (((Point *)p1)->x > ((Point *)p2)->x)
        return 1;
    if (((Point *)p1)->x < ((Point *)p2)->x)
        return -1;
    return 0;
}

int compare_y(const void* p1, const void* p2) {
    if (((Point *)p1)->y > ((Point *)p2)->y)
        return 1;
    if (((Point *)p1)->y < ((Point *)p2)->y)
        return -1;
    return 0;
}

/////

inline double get_distance(Point *p1, Point *p2) {
    return sqrt((p1->x - p2->x)*(p1->x - p2->x) + (p1->y - p2->y)*(p1->y - p2->y));
}

double minimal_distance_small(Point *points, size_t n) {
    if (n == 2) {
        return get_distance(points, points + 1);
    } else {
        return min(min(get_distance(points, points + 1), get_distance(points, points + 2)), get_distance(points + 1, points + 2));
    }
    return -1;
}

double minimal_distance_filtred(Point *points_sy, size_t n, double min) {
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n && points_sy[j].y - points_sy[i].y < min; j++) {
            double d = get_distance(points_sy + j, points_sy + i);
            if (d < min) {
                min = d;
                mp[0] = points_sy[i];
                mp[1] = points_sy[j];
            }
        }
    return min;
}



double get_minial_distance(Point *points_sx, Point *points_sy, size_t n) {
    if (n < 4)
        return minimal_distance_small(points_sx, n);
    
    size_t mid_n = n / 2;
    Point *mid_point = points_sx + mid_n;
    Point points_syl[n];
    Point points_syr[n];
    size_t li = 0, ri = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (points_sy[i].x <= mid_point->x && li < mid_n) {
            points_syl[li++] = points_sy[i];
        } else {
            points_syr[ri++] = points_sy[i];
        }
    }
    
    double dl = get_minial_distance(points_sx, points_syl, li);
    double dr = get_minial_distance(mid_point, points_syr, ri);
    double d = min(dl, dr);
    
    Point midPoints[n];
    size_t mpi = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (abs(points_sy[i].x - mid_point->x) < d) {
            midPoints[mpi++] = points_sy[i];
        }
    }
    
    return  minimal_distance_filtred(midPoints, mpi, d);
}

double minimal_distance(Point *points, Point *points_copy, size_t n) {
    if (n == 1)
        return 0;
    std::qsort(points, n, sizeof(Point), compare_x);
    std::qsort(points_copy, n, sizeof(Point), compare_y);
    return get_minial_distance(points, points_copy, n);
}




/////////////////////

double lacmus(Point *points, size_t n) {
    
    if (n == 1)
        return 0;
    
    double md = get_distance(points , points + 1);
    
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++) {
            double d = get_distance(points + i, points +j);
            if (d < md) {
                md = d;
                rp[0] = points[i];
                rp[1] = points[j];
            }
        }
    
    return md;
}

int main() {
    
    size_t n;
    std::cin >> n;
    
    Point *points = (Point *)malloc(sizeof(Point) * n);
    Point *points_copy = (Point *)malloc(sizeof(Point) * n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
        points_copy[i] = points[i];
    }
    
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(points, points_copy, n) << "\n";
    free(points);
    free(points_copy);
    
    return 0;
}


