#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::min;


int edit_distance(const string &str1, const string &str2) {
    
    int j_max = (int)str1.size() + 1;
    int i_max = (int)str2.size() + 1;
    
    int matrix[j_max][i_max];
    
    for(int j = 0; j < j_max; j++)
        for(int i = 0; i < i_max; i++) {
            if (j == 0) {
                matrix[j][i] = i;
                continue;
            }
            if (i == 0) {
                matrix[j][i] = j;
                continue;
            }
            int insert = matrix[j][i - 1] + 1;
            int deletion = matrix[j - 1][i] + 1;
            int match = matrix[j - 1][i - 1];
            int mismatch = match + 1 ;
            
            if (str1[j - 1] == str2[i - 1]) {
                matrix[j][i] = min(min(insert, deletion), match);
            } else {
                matrix[j][i] = min(min(insert, deletion), mismatch);
            }
        }
    
    return matrix[j_max - 1][i_max - 1];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}

