#include <iostream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <list>

using std::vector;
using std::max;
using std::list;

struct Point {
    int x;
    int y;
    int z;
    
    Point() {
        x = -1;
        y = -1;
        z = -1;
    }
    Point(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Node {
    Node *next;
    Point point;
    
    Node(Point &_point) {
        next = NULL;
        point = _point;
    }
};

struct Chain {
    Node *root;
    size_t size;
    
    Chain() {
        root = NULL;
        size = 0;
    }
    
    Chain* add_point(Point &point) {
        Chain *newChain = new Chain();
        newChain->size = size + 1;
        
        if (root == NULL) {
            newChain->root = new Node(point);
        } else {
            Node *current = root;
            Node *currentNew = NULL;
            newChain->root = currentNew = new Node(current->point);
            current = current->next;
            if (current != NULL) {
                do {
                    
                    currentNew->next = new Node(current->point);
                    currentNew = currentNew->next;
                    current = current->next;
                    if (current == NULL) {
                        break;
                    }
                } while(current->next != NULL);
            }
            currentNew->next = new Node(point);
        }
        
        return newChain;
    }
    
};


bool isAlreadyUsed(Node *node, const Point &newPoint) {
    while (node != NULL) {
        if (node->point.x == newPoint.x || node->point.y == newPoint.y || node->point.z == newPoint.z) {
            return true;
        }
        node = node->next;
    }
    return false;
}

int lcs3(vector<long> &a, vector<long> &b, vector<long> &c) {
    
    size_t xN = a.size();
    size_t yN = b.size();
    size_t zN = c.size();
    
    size_t lN = xN + yN + zN;
    
    Chain* matrix[xN][yN][zN];
    matrix[0][0][0] = new Chain();
    
    if (a[0] == b[0] && b[0] == c[0]) {
        Point p = Point(0, 0, 0);
        matrix[0][0][0] = matrix[0][0][0]->add_point(p);
    }
    
    for (size_t level = 1; level < lN; level++)
        for (size_t x = 0; x <= level; x++)
            for(size_t y = 0; y <= level - x; y++) {
                size_t z = level - x - y;
                if (x >= xN || y >= yN || z >= zN)
                    continue;
                int new_point = (a[x] == b[y] && b[y] == c[z]) ? 1 : 0;
                if (new_point == 0) {
                    Chain *maxChain = NULL;
                    if (x > 0) {
                        maxChain = matrix[x - 1][y][z];
                    }
                    if (y > 0 && (!maxChain || matrix[x][y - 1][z]->size >= maxChain->size)) {
                        maxChain = matrix[x][y - 1][z];
                    }
                    if (z > 0 && (!maxChain || matrix[x][y][z - 1]->size >= maxChain->size)) {
                        maxChain = matrix[x][y][z - 1];
                    }
                    if (maxChain == NULL) {
                        assert(0);
                    }
                    matrix[x][y][z] = maxChain;
                } else {
                    Chain *maxChain = NULL;
                    size_t size = 0;
                    Point newPoint((int)x, (int)y, (int)z);
                    
                    if (x > 0) {
                        maxChain = matrix[x - 1][y][z];
                        size = maxChain->size;
                        if (isAlreadyUsed(maxChain->root, newPoint) == false) {
                            size++;
                        }
                    }
                    if (y > 0 && matrix[x][y - 1][z]->size >= size) {
                        maxChain = matrix[x][y - 1][z];
                        size = maxChain->size;
                        if (isAlreadyUsed(maxChain->root, newPoint) == false) {
                            size++;
                        }
                    }
                    if (z > 0 && matrix[x][y][z - 1]->size >= size) {
                        maxChain = matrix[x][y][z - 1];
                        size = maxChain->size;
                        if (isAlreadyUsed(maxChain->root, newPoint) == false) {
                            size++;
                        }
                    }
                    
                    if (size > maxChain->size || size == 0) {
                        maxChain = maxChain->add_point(newPoint);
                    }
                    if (maxChain == NULL) {
                        assert(0);
                    }
                    matrix[x][y][z] = maxChain;
                }
                
                
            }
    
    
    return (int)matrix[xN - 1][yN - 1][zN - 1]->size;
}

int main() {
    size_t an;
    std::cin >> an;
    vector<long> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<long> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<long> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
