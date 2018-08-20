#include <iostream>

long long lcm_naive(int a, int b) {
    for (long l = 1; l <= (long long) a * b; ++l)
        if (l % a == 0 && l % b == 0)
            return l;
    
    return (long long) a * b;
}

unsigned long long gcd_fast(unsigned long long a, unsigned long long b) {
    return b == 0 ? a : gcd_fast(b, a % b);
}

unsigned long long lcm_fast(unsigned long long a, unsigned long long b) {
    return  a / gcd_fast(a, b) * b;
}


int main() {
    unsigned long long a, b;
    std::cin >> a >> b;
    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}


