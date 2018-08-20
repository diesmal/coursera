#include <iostream>
#include <algorithm>
#include <vector>

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    std::vector<int> v{1, 1};
    while (true) {
        int t = (v[v.size() - 1] + v[v.size() - 2]) % 10;
        v.push_back(t);
        if (t == 0 && v.size() % 2 == 0 &&
            std::equal(v.begin(), v.begin() + v.size() / 2,
                       v.begin() + v.size() / 2, v.end())) {
                
                
                from = from % 60;
                to = to % 60;
                if (to < from) {
                    to += 60;
                }
                
                int sum = 0;
                
                sum = 0;
                
                for(int i = (int)from; i <= to; i++) {
                    sum = (sum + v[i - 1]) % 10;
                }
                
                return sum;
            }
    }
    return 0;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}


