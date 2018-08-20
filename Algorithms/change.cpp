#include <iostream>

int main() {
    long m;
    std::cin >> m;
    std::cout <<  ((m / 10) + ((m % 10) / 5) + (m % 10) % 5) << '\n';
}

