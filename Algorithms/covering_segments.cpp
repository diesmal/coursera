#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
    long start, end;
};

void qsort(vector<Segment> &arr, long left, long right) {
    if (left < right){
        long pivot = right;
        for (long i = left; i < pivot; i++) {
            if (arr[i].start > arr[pivot].start) {
                Segment tmp = arr[pivot];
                arr[pivot] = arr[i];
                arr[i] = arr[pivot - 1];
                arr[pivot - 1] = tmp;
                pivot--;
                i--;
            }
        }
        qsort(arr, left, pivot - 1);
        qsort(arr, pivot, right);
    }
}

void sort(vector<Segment> &array) {
    qsort(array, 0, array.size() - 1);
}

vector<long> optimal_points(vector<Segment> &segments) {
    vector<long> points;
    
    sort(segments);
    
    Segment start = segments[0];
    
    for (size_t i = 0; i < segments.size(); ++i) {
        if (segments[i].start > start.end) {
            points.push_back(start.end);
            start = segments[i];
        } else if (segments[i].end < start.end) {
            start.end = segments[i].end;
        }
    }
    points.push_back(start.end);
    return points;
}


int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<long> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}


