#include <iostream>
#include <vector>

using std::vector;

vector<long> optimal_summands(long n) {
    vector<long> summands;
    
    for (long i = 1; i <= n; i++) {
        long left = n - i;
        if (left > i) {
            summands.push_back(i);
            n = left;
        } else {
            summands.push_back(n);
            break;
        }
    }
    
    return summands;
}

int main() {
    long n;
    std::cin >> n;
    vector<long> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}

