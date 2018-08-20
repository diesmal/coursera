#include <iostream>
#include <algorithm>
#include <vector>


long fibonacci_sum_fast(long long n) {
    
    std::vector<int> v{1, 1};
    while (true) {
        int t = (v[v.size() - 1] + v[v.size() - 2]) % 10;
        v.push_back(t);
        if (t == 0 && v.size() % 2 == 0 &&
            std::equal(v.begin(), v.begin() + v.size() / 2,
                       v.begin() + v.size() / 2, v.end())) {
                
                
                int sum = 0;
                for (int i =0; i < n % 60; i++) {
                    sum = (sum + v[i]) % 10;
                }
                return sum;
            }
    }
    return 0;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}


