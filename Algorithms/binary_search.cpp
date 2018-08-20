#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

long binary_search(const vector<size_t> &a, size_t x) {
    size_t left = 0, right = (size_t)a.size();
    
    while (left <= right) {
        size_t middle = (right - left)/2 + left;
        
        if (a[middle] == x) {
            return middle;
        }
        
        if (a[middle] > x) {
            if (middle == 0) {
                return -1;
            }
            right = middle - 1;
        } else {
            if (middle == a.size() - 1) {
                return -1;
            }
            left = middle + 1;
        }
    }
    
    return -1;
}

long linear_search(const vector<size_t> &a, size_t x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<size_t> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    size_t m;
    std::cin >> m;
    vector<long> b(m);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    
    for (int i = 0; i < m; ++i) {
        //replace with the call to binary_search when implemented
        std::cout << binary_search(a, b[i]) << ' ';
    }
}

