#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::list;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }
    
public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems.resize(bucket_count, list<string>(0));
        
    }
    
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }
    
    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    
    void processQuery(const Query& query) {
        if (query.type == "check") {
            for(auto it = elems[query.ind].rbegin(); it != elems[query.ind].rend(); it++) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        } else {
            size_t hashValue = hash_func(query.s);
            
            if (query.type == "find") {
                bool is_found = false;
                for(auto it = elems[hashValue].begin(); it != elems[hashValue].end(); it++) {
                    if (*it == query.s) {
                        is_found = true;
                        break;
                    }
                }
                writeSearchResult(is_found);
            } else if (query.type == "add") {
                bool is_found = false;
                for(auto it = elems[hashValue].begin(); it != elems[hashValue].end(); it++) {
                    if (*it == query.s) {
                        is_found = true;
                        break;
                    }
                }
                if (!is_found) {
                    elems[hashValue].push_back(query.s);
                }
            } else if (query.type == "del") {
                for(auto it = elems[hashValue].begin(); it != elems[hashValue].end(); it++) {
                    if (*it == query.s) {
                        elems[hashValue].erase(it);
                        break;
                    }
                }
            }
        }
    }
    
    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}


