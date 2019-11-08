#include "MinOst.h"

int Graph::ReturnLength(vector<int> permutation) {
    int len = 0;
    for (int i = 0; i < permutation.size() - 1; i++){
        len += g[permutation[i]][permutation[i + 1]];
    }
    
    return len;
}

double Graph::Sort() {
    vector<int> permutation;
    int minimum = 100000000;
    
    for(int i = 0; i < n; i++){
        permutation.push_back(i);
    }
    
    do {
        minimum = min(minimum, ReturnLength(permutation));
    } while(next_permutation(permutation.begin(), permutation.end()) );
    
    return minimum;
}
