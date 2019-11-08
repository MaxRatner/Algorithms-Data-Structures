//
//  main.cpp
//  Z-func
//
//  Created by Maxim Fominykh on 30/09/2018.
//  Copyright © 2018 Maxim Fominykh. All rights reserved.
//

#include <vector>
#include <iostream>

std::vector<int> z_func(std::string& s) {//returns z-array
    int n = (int)s.length();
    std::vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (z[i] != 0) {
            l = i;
            r = z[i] + i - 1;
        }
    }
    
    return z;
}

int main() {
    std::string pattern, z_str;
    std::cin >> pattern;
    long pattern_size = pattern.length();
    std::cin >> z_str;
    z_str = pattern + '$' + z_str;
    std::vector<int> z = z_func(z_str); //array of z-values
    for (long i = pattern_size + 1; i < z.size(); i++) {
        if (pattern_size == z[i]) {
            std::cout << i - pattern_size - 1 << ' ';
        }
    }
    
    return 0;
}
