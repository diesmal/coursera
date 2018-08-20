#include <iostream>
#include <cassert>
#include <string>

using std::string;
using std::max;
using std::min;

long long eval(long long a, char op, long long b) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}


long long get_maximum_value(const string &exp) {
    
    size_t N = exp.size()/2 + 1;
    
    long long mina[N][N];
    long long maxa[N][N];
    
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++) {
            mina[i][j] = maxa[i][j] = 0;
        }
    
    for (size_t i = 0; i < N; i++) {
        mina[i][i] = maxa[i][i] = exp[i * 2] - 48;
    }
    
    for (size_t a = 1; a < N; a++) {
        size_t i = 0;
        for(size_t j = a; j < N; i++, j++) {
            if (i == j - 1) {
                mina[i][j] = maxa[i][j] = eval(mina[i][j - 1], exp[(j - 1) * 2 + 1], mina[i + 1][j]);
                continue;
            }
            long long mivs = 2147483647;
            long long maxs = -2147483647;

            for (long long k = i; k < j; k++) {
                long long a = eval(maxa[i][k], exp[k * 2 + 1], maxa[k + 1][j]);
                long long b = eval(maxa[i][k], exp[k * 2 + 1], mina[k + 1][j]);
                long long c = eval(mina[i][k], exp[k * 2 + 1], maxa[k + 1][j]);
                long long d = eval(mina[i][k], exp[k * 2 + 1], mina[k + 1][j]);
                
                mivs = min(mivs, min(min(a, b), min(c, d)));
                maxs = max(maxs, max(max(a, b), max(c, d)));
            }
            
            maxa[i][j] = maxs;
            mina[i][j] = mivs;
        }
    }
    
    return maxa[0][N - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}


