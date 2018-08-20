#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

//#define DDEBUG

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    long long key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;
    
    Vertex(long long key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
    : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

#ifdef DDEBUG
void print_tree(Vertex *v) {
    
    if (v != NULL) {
        std::cout << v->key << "(";
        std::cout << v->sum << ",";
        if (v->left == NULL) {
            std::cout << "lnull,";
        }
        if (v->right == NULL) {
            std::cout << "rnull";
        }
        if (v->parent == NULL) {
            std::cout << "pnull";
        }
        std::cout << ") ";
        print_tree(v->left);
        print_tree(v->right);
    }
}
#endif

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
        } else {
            big_rotation(v);
        }
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, long long key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, long long key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(long long x) {
#ifdef DDEBUG
    std::cout << "Insert: " << x << std::endl;
#endif
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void erase(long long x) {
#ifdef DDEBUG
    std::cout << "Erase: " << x << std::endl;
#endif
    Vertex* nearesrt = find(root, x);
    if ((nearesrt != NULL) && (nearesrt->key == x)) {
        if (root->left != NULL) {
            root->left->parent = NULL;
        }
        if (root->right != NULL) {
            root->right->parent = NULL;
        }
        root = merge(root->left, root->right);
       // delete nearesrt;
    }
}

bool find(long long x) {
#ifdef DDEBUG
    std::cout << "Find: " << x << std::endl;
#endif
    Vertex* nearesrt = find(root, x);
    return ((nearesrt != NULL) && (nearesrt->key == x));
}

long long sum(long long from, long long to) {
#ifdef DDEBUG
    std::cout << "Sum from " << from << " to " << to << std::endl;
#endif
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    
#ifdef DDEBUG
    std::cout << "MIDDLE: ";
    print_tree(middle);
    std::cout << std::endl;
#endif
    
    ans = middle->sum;
    
    return ans;
}

const long long MODULO = 1000000001;

int main(){
    long long n;
    std::cin >> n;
    long long last_sum_result = 0;
    long long commands[n][3];
    //0 - +
    //1 - -
    //2 - ?
    //3 - s
    
    for (long long i = 0; i < n; i++) {
        char type;
        std::cin >> type;
        switch (type) {
            case '+' : {
                long long x;
                std::cin >> x;
                commands[i][0] = 0;
                commands[i][1] = x;
            } break;
            case '-' : {
                long long x;
                std::cin >> x;
                commands[i][0] = 1;
                commands[i][1] = x;
            } break;
            case '?' : {
                long long x;
                std::cin >> x;
                commands[i][0] = 2;
                commands[i][1] = x;
            } break;
            case 's' : {
                long long l, r;
                std::cin >> l >> r;
                commands[i][0] = 3;
                commands[i][1] = l;
                commands[i][2] = r;
            }
        }
    }
    
    for (long long i = 0; i < n; i++) {
        switch (commands[i][0]) {
            case 0:
                insert((commands[i][1] + last_sum_result) % MODULO);
#ifdef DDEBUG
                print_tree(root);
                std::cout << std::endl;
#endif
                break;
            case 1:
                erase((commands[i][1] + last_sum_result) % MODULO);
#ifdef DDEBUG
                print_tree(root);
                std::cout << std::endl;
#endif
                break;
            case 2:
                printf(find((commands[i][1] + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
                break;
            default:
                long long res = sum((commands[i][1] + last_sum_result) % MODULO, (commands[i][2] + last_sum_result) % MODULO);
                printf("%lld\n", res);
                last_sum_result = res % MODULO;
                break;
        }
    }
#ifdef DDEBUG
    printf("end");
#endif
    return 0;
}

