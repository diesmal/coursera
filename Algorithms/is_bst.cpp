#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    long long key;
    long long left;
    long long right;
    
    Node() : key(0), left(-1), right(-1) {}
    Node(long long key_, long long left_, long long right_) : key(key_), left(left_), right(right_) {}
};

bool _checkNode(long long node_idx, long long min, long long max, const vector<Node>& tree) {
    if (node_idx >= 0) {
        if (tree[node_idx].key >= min && tree[node_idx].key < max) {
            return (_checkNode(tree[node_idx].left, min, tree[node_idx].key, tree)) &&
            (_checkNode(tree[node_idx].right, tree[node_idx].key, max, tree));
        }
        return false;
    }
    return true;
}


bool IsBinarySearchTree(const vector<Node>& tree) {
    if (tree.size() < 2) {
        return true;
    }
    long long min = std::numeric_limits<long long>::min();
    long long max = std::numeric_limits<long long>::max();
    
    return _checkNode(0, min, max, tree);
}

int main() {
    long long nodes;
    cin >> nodes;
    vector<Node> tree;
    for (long long i = 0; i < nodes; ++i) {
        long long key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}

