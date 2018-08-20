#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

struct PivotRanged {
    size_t left;
    size_t right;
};

void qsort(vector<size_t> &arr, size_t left, size_t right) {
    if (left < right){
        PivotRanged pivot = {right, right};
        for (long long i = left; i < pivot.left; i++) {
            
            if (arr[i] == arr[pivot.right]) {
                swap(arr[i], arr[pivot.left - 1]);
                pivot.left--;
                if (i >= 0) {
                    i--;
                }
            } else if (arr[i] > arr[pivot.right]) {
                swap(arr[i], arr[pivot.right]);
                swap(arr[i], arr[pivot.left - 1]);
                pivot.left--;
                pivot.right--;
                if (i >= 0) {
                    i--;
                }
            }
        }
        
        if (pivot.left > 0) {
            qsort(arr, left, pivot.left - 1);
        }
        qsort(arr, pivot.right, right);
    }
}

void sort(vector<size_t> &array) {
    qsort(array, 0, array.size() - 1);
}

int main() {
    size_t n;
    std::cin >> n;
    vector<size_t> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    sort(a);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}

