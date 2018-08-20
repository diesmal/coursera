#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

struct Stat {
    long number;
    long count;
};

long get_majority_element(vector<long> &a, long left, long right) {
    
    Stat max = {0, 0};
    Stat pre = {0, 0};
    size_t n = a.size();
    
    for (size_t i = 0; i < n; i++) {
        if (max.number == a[i]) {
            max.count++;
        } else if (pre.number == a[i]) {
            pre.count++;
            if (pre.count > max.count) {
                Stat tmp = max;
                max = pre;
                pre = tmp;
            }
        } else {
            pre.number = a[i];
            pre.count = 1;
        }
        
    }
    
    size_t count = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (a[i] == max.number) {
            count++;
        }
    }
    
    if (count > n/2) {
        return 1;
    }
    
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<long> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}


