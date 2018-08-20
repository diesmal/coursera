#include <iostream>

void qsort(long *arr, long left, long right) {
    if (left < right){
        long pivot = right;
        for (long i = left; i < pivot; i++) {
            if (arr[i] > arr[pivot]) {
                long tmp = arr[pivot];
                arr[pivot] = arr[i];
                arr[i] = arr[pivot - 1];
                arr[pivot - 1] = tmp;
                pivot--;
                i--;
            }
        }
        qsort(arr, left, pivot - 1);
        qsort(arr, pivot, right);
    }
    
    
}

void sort(long *array, long N) {
    qsort(array, 0, N - 1);
}

long long max_dot_product(long *profit, long *clicks, long N) {
    sort(profit, N);
    sort(clicks, N);
    long long result = 0;
    for (long i = 0; i < N; i++) {
        result += ((long long) profit[i]) * clicks[i];
        
    }
    return result;
}

int main() {
    long n;
    std::cin >> n;
    long *profit = (long *)malloc(sizeof(long) * n);
    long *clicks = (long *)malloc(sizeof(long) * n);
    
    for (long i = 0; i < n; i++) {
        std::cin >> profit[i];
    }
    for (long i = 0; i < n; i++) {
        std::cin >> clicks[i];
    }
    std::cout << max_dot_product(profit, clicks, n) << std::endl;
}

