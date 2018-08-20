#include <iostream>
#include <algorithm>
#include <vector>


long longget_fibonacci_huge_fast(long long n, long long m) {
    if (m == 2) {
        return  (n % 3) ? 1 : 0;
    }
    
    
    std::vector<long long> v{1, 1};
    while (true) {
        auto t = (v[v.size() - 1] + v[v.size() - 2]) % m;
        v.push_back(t);
        if (t == 0 && v.size() % 2 == 0 &&
            std::equal(v.begin(), v.begin() + v.size() / 2,
                       v.begin() + v.size() / 2, v.end())) {
                return v[n % (v.size() / 2) - 1];
            }
    }
    return 0;
}

int main() {
    unsigned long long n, m;
    std::cin >> n >> m;
    std::cout << longget_fibonacci_huge_fast(n, m) << '\n';
}

