#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;
    
    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }
    
    int getParent(int table) {
        if (sets[table].parent < 0)
            return table;
        int parent = sets[table].parent;
        while (sets[parent].parent != parent)
            parent = sets[parent].parent;
        sets[table].parent = parent;
        return parent;
    }
    
    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        //        cout << "realDestination " << realDestination + 1 << endl;
        //        caout << "realSource " << realSource + 1 << endl;
        if (sets[realDestination].rank < sets[realSource].rank) {
            std::swap(realDestination, realSource);
        }
        if (realDestination != realSource) {
            sets[realDestination].size += sets[realSource].size;
            //            cout << "size " << sets[realDestination].size << endl;
            sets[realSource].parent = realDestination;
            sets[realDestination].rank++;
            if (sets[realDestination].size > max_table_size)
                max_table_size = sets[realDestination].size;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }
    
    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;
        
        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }
    
    return 0;
}
