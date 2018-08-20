#include <iostream>
#include <vector>

using std::vector;


void qsort(vector<long> &starts, vector<long> &ends, long left, long right) {
    if (left < right){
        long pivot = right;
        for (long i = left; i < pivot; i++) {
            if (starts[i] > starts[pivot]) {
                std::swap(starts[pivot], starts[i]);
                std::swap(starts[pivot - 1], starts[i]);
                
                std::swap(ends[pivot], ends[i]);
                std::swap(ends[pivot - 1], ends[i]);
                
                pivot--;
                i--;
            }
        }
        qsort(starts, ends, left, pivot - 1);
        qsort(starts, ends, pivot, right);
    }
}

void sort(vector<long> &starts, vector<long> &ends) {
    qsort(starts, ends, 0, starts.size() - 1);
}

vector<long> count_segments(vector<long> starts, vector<long> ends, vector<long> points) {
    sort(starts, ends);
    vector<long> cnt(points.size());
    
    for(size_t i = 0; i < points.size(); i++) {
        long count = 0;
        for (int y = 0; y < starts.size() && starts[y] <= points[i]; y++) {
            if (ends[y] >= points[i]) {
                count++;
            }
        }
        cnt[i] = count;
    }
    
    return cnt;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    vector<long> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<long> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    
    vector<long> cnt = count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}

