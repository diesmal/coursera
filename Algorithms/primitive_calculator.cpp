#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct node {
    node *parent;
    int value;
    
    node(int _value, node *_parent) {
        value = _value;
        parent = _parent;
    }
};

struct lvl {
    lvl *next;
    node *data;
    
    lvl(node *_data) {
        next = NULL;
        data = _data;
    }
    
};

void optimal_sequence(int n) {
    node root = node(n, NULL);
    lvl *currentLvl = new lvl(&root);
    
    node *firstone = NULL;
    int count = 0;
    while (firstone == NULL) {
        lvl *nextLvl = new lvl(0);
        lvl *rootLvl = nextLvl;
        
        while (currentLvl != NULL) {
            int value = currentLvl->data->value;
            if (value == 1) {
                firstone = currentLvl->data;
                currentLvl = NULL;
                continue;
            }
            if (value % 3 == 0) {
                node *newNode = new node(value / 3, currentLvl->data);
                nextLvl->next = new lvl(newNode);
                nextLvl = nextLvl->next;
            }
            if (value % 2 == 0) {
                node *newNode = new node(value / 2, currentLvl->data);
                nextLvl->next = new lvl(newNode);
                nextLvl = nextLvl->next;
            }
            if (value - 1 > 0){
                node *newNode = new node(value - 1, currentLvl->data);
                nextLvl->next = new lvl(newNode);
                nextLvl = nextLvl->next;
            }
            lvl *tmpLvl = currentLvl;
            currentLvl = currentLvl->next;
            free(tmpLvl);
        }
        currentLvl = rootLvl->next;
        free(rootLvl);
        count++;
    }
    
    std::cout << count - 1 << std::endl;
    
    while (firstone != NULL) {
        std::cout << firstone->value << " ";
        firstone = firstone->parent;
    }
    
    //    std::vector<int> sequence;
    //    while (n >= 1) {
    //        sequence.push_back(n);
    //        if (n % 3 == 0) {
    //            n /= 3;
    //        } else if (n % 2 == 0) {
    //            n /= 2;
    //        } else {
    //            n = n - 1;
    //        }
    //    }
    //    reverse(sequence.begin(), sequence.end());
    //    return sequence;
}

int main() {
    int n;
    
    std::cin >> n;
    optimal_sequence(n);
    //    vector<int> sequence = optimal_sequence(n);
    //    std::cout << sequence.size() - 1 << std::endl;
    //    for (size_t i = 0; i < sequence.size(); ++i) {
    //        std::cout << sequence[i] << " ";
    //    }
}

