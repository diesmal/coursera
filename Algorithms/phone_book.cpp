#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    size_t number;
};

struct Record {
    string name;
};

vector<Record *> contacts(10000000, NULL);

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            contacts[queries[i].number] = new Record();
            contacts[queries[i].number]->name = queries[i].name;
        } else if (queries[i].type == "del") {
            if (contacts[queries[i].number] != NULL) {
                free(contacts[queries[i].number]);
                contacts[queries[i].number] = NULL;
            }
        } else {
            string response = "not found";
            if (contacts[queries[i].number] != NULL) {
                response = contacts[queries[i].number]->name;
            }
            result.push_back(response);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
