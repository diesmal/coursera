#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

long inversions = 0;

std::vector<long> mergesort(vector<long> &array) {
    if (array.size() <= 1) {
        return array;
    }
    
    std::size_t const half_size = array.size() / 2;
    std::vector<long> split_lo(array.begin(), array.begin() + half_size);
    std::vector<long> split_hi(array.begin() + half_size, array.end());
    
    std::vector<long> sorted_lo =  mergesort(split_lo);
    std::vector<long> sorted_hi =  mergesort(split_hi);
    
    size_t i_lo = 0;
    size_t i_hi = 0;
    
    for (size_t i = 0; i < array.size(); i++) {
        if (i_lo != sorted_lo.size() &&
            (i_hi == sorted_hi.size() || sorted_hi[i_hi] >= sorted_lo[i_lo])) {
            array[i] = sorted_lo[i_lo];
            i_lo++;
        } else {
            array[i] = sorted_hi[i_hi];
            if (i_lo != sorted_lo.size()) {
                long delta = sorted_lo.size() + i_hi - i;
                inversions += delta;
            }
            i_hi++;
        }
    }
    return array;
}


int main() {
    size_t n;
    std::cin >> n;
    vector<long> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    a = mergesort(a);
    
    std::cout << inversions;
    
}


