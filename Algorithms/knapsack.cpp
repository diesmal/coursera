#include <iostream>
#include <vector>
#include <algorithm>


using std::vector;

void print_a( vector< vector<int> > matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for(size_t j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}

void print_a1( vector<int> arr) {
    std::cout << std::endl;
    for(size_t j = 0; j < arr.size(); j++) {
        std::cout << arr[j] << " ";
    }
    std::cout << std::endl;
}

void qsort(vector<int> &arr, long left, long right) {
    if (left < right){
        long pivot = right;
        for (long i = left; i < pivot; i++) {
            if (arr[i] > arr[pivot]) {
                int tmp = arr[pivot];
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

int optimal_weight(int W, vector<int> &w) {
    qsort(w, 0, w.size() - 1);
    //    print_a1(w);
    vector< vector<int> > matrix(W + 1,vector<int>(w.size() + 1));
    
    for (size_t j = 0; j <= w.size(); j++) {
        for (int i = 0; i <= W; i++) {
            int newValue = 0;
            if (j > 0) newValue = w[j - 1];
            if (j == 0) {
                matrix[i][j] = 0;
                continue;
            }
            if (j == 1) {
                matrix[i][j] = (i - newValue >= 0) ? newValue : 0;
                continue;
            }
            if (i - newValue < 0) {
                matrix[i][j] = matrix[i][j - 1];
                continue;
            }
            
            int possible = newValue + matrix[i - newValue][j - 1];
            matrix[i][j] = std::max(possible, matrix[i][j - 1]);
        }
    }
    
    
    
    return matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1];
    
    //    print_a(matrix);
    //
    //    int current_weight = 0;
    //    for (size_t i = 0; i < w.size(); ++i) {
    //        if (current_weight + w[i] <= W) {
    //            current_weight += w[i];
    //        }
    //    }
    //    return current_weight;
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}

