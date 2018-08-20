#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

inline size_t parentIndex(size_t childIndex) {
    return (childIndex > 0) ? (childIndex - 1)/2 : 0;
}

inline size_t leftChildIndex(size_t parentIndex) {
    return 2 * parentIndex + 1;
}

inline size_t rightChildIndex(size_t parentIndex) {
    return 2 * parentIndex + 2;
}

class HeapBuilder {
private:
    vector<long> data_;
    vector< pair<long, long> > swaps_;
    
    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (long i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }
    
    
    
    void ReadData() {
        long n;
        cin >> n;
        data_.resize(n);
        for(long i = 0; i < n; ++i)
            cin >> data_[i];
    }
    
    void shiftUp(size_t c) {
        do {
            size_t p = parentIndex(c);
            if (data_[p] > data_[c]) {
                swap(data_[p], data_[c]);
                swaps_.push_back(make_pair(p, c));
                c = p;
            } else {
                c = 0;
            }
        } while (c > 0);
    }
    
    void shiftDown(size_t p) {
        do {
            size_t lc = leftChildIndex(p);
            size_t rc = rightChildIndex(p);
            lc = (lc < data_.size()) ? lc : p;
            rc = (rc < data_.size()) ? rc : p;
            size_t c = (data_[lc] > data_[rc]) ? rc : lc;
            
            if (data_[p] > data_[c]) {
                swap(data_[p], data_[c]);
                swaps_.push_back(make_pair(p, c));
                p = c;
            } else {
                p = 0;
            }
        } while (p > 0);
    }
    
    void GenerateSwaps() {
        swaps_.clear();
        
        for(size_t i = data_.size() - 1; i > 0; i--) {
            shiftUp(i);
            shiftDown(i);
        }
    }
    
public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
