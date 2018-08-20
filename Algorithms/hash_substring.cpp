#include <iostream>
#include <string>
#include <vector>

using std::string;

struct Data {
    string pattern;
    string text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

unsigned long long getHash(string s) {
    unsigned long long hash = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        hash += s[i];
    }
    return hash;
}

void print_occurrences(const std::vector<size_t>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<size_t> get_occurrences(const Data& input) {
    std::vector<size_t> ans;
    if (input.text.length() < input.pattern.length()) {
        return ans;
    }
    
    unsigned long long pattern_hash = getHash(input.pattern);
    unsigned long long substring_hash = getHash(input.text.substr(0, input.pattern.length()));
    
    size_t finish = input.text.length() - input.pattern.length();
    for (size_t i = 0; i <= finish; i++) {
        if (pattern_hash == substring_hash) {
            if (input.text.substr(i, input.pattern.length()) == input.pattern) {
                ans.push_back(i);
            }
        }
        substring_hash += (input.text[i + input.pattern.size()] - input.text[i]);
    }
    
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}

