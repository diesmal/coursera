#include <iostream>

struct WV {
    long *weights;
    long *values;
};

void qsort(WV data, long left, long right) {
    if (left < right){
        long pivot = right;
        for (long i = left; i < pivot; i++) {
            if ((double)data.values[i]/(double)data.weights[i] < (double)data.values[pivot]/(double)data.weights[pivot]) {
                long tmpv = data.values[pivot];
                long tmpw = data.weights[pivot];
                data.values[pivot] = data.values[i];
                data.weights[pivot] = data.weights[i];
                data.values[i] = data.values[pivot - 1];
                data.weights[i] = data.weights[pivot - 1];
                data.values[pivot - 1] = tmpv;
                data.weights[pivot - 1] = tmpw;
                pivot--;
                i--;
            }
        }
        qsort(data, left, pivot - 1);
        qsort(data, pivot, right);
    }
    
    
}

void sort(WV array, long N) {
    qsort(array, 0, N - 1);
}

double get_optimal_value(long capacity, WV data, long N) {
    double value = 0.0;
    sort(data, N);
    
    for (long i = 0; i < N; i++) {
        if (data.weights[i] <= capacity) {
            value += data.values[i];
            capacity -= data.weights[i];
        } else {
            value += ((double)capacity / (double)data.weights[i] * (double)data.values[i]);
            return value;
        }
    }
    return value;
}

int main() {
    long n;
    long capacity;
    std::cin >> n >> capacity;
    WV data;
    data.weights = (long *)malloc(sizeof(long) * n);
    data.values = (long *)malloc(sizeof(long) * n);
    
    for (long i = 0; i < n; i++) {
        std::cin >> data.values[i] >> data.weights[i];
    }
    
    double optimal_value = get_optimal_value(capacity, data, n);
    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}

