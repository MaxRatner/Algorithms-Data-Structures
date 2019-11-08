//
//  main.cpp
//  suff_mass
//
//  Created by Maxim Fominykh on 30/10/2018.
//  Copyright © 2018 Maxim Fominykh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>

std::vector<int> Build_LCP(std::string s, std::vector<int> suf, int l) {
    std::vector<int> lcp (l); // vector of largest common prefixes
    int pos [l]; // pos[] — array, inverse to array suf
    for (int i = 0; i < l ; i++) {
        pos[suf[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < l ; i++){
        if (k > 0){
            k--;
        }
        if (pos[i] == l - 1){
            lcp[l - 1] =  - 1;
            k = 0;
        } else {
            int j = suf[pos[i] + 1];
            while (std::max(i + k, j + k) < l && s[i + k] == s[j + k]) {
                k++;
            }
            lcp[pos[i]] = k;
        }
    }
    return lcp;
    
}

std::vector<int> Build_Suf_Array(std::string s, int l) {
    const int alphabet = 256; // alphabet size, <= l
    
    // zero - phase
    std::vector<int> suffix_array(l);// suffix array
    int cnt[alphabet];// array for bit-by-bit sorting
    int classes[l*1000000];  // array for clases of equivalence
    memset(cnt, 0, alphabet * sizeof(int)); // filling with zeros (first initialization)
    
    for (int i = 0; i < l; i++){
        cnt[s[i]]++;
    }
    for (int i = 1; i < alphabet; i++){
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < l; i++){
        suffix_array[--cnt[s[i]]] = i;
    }
    
    classes[suffix_array[0]] = 0;
    int quantity_of_classes = 1;
    for (int i = 1; i < l; i++) {
        if (s[suffix_array[i]] != s[suffix_array[i - 1]]){
            ++quantity_of_classes;
        }
        classes[suffix_array[i]] = quantity_of_classes - 1;
    }
    
    
    // basic phases
    int suf_sort[l];// suffix array sorted by second part of strings
    int new_classes[l]; //classes for 2^h-length strings
    
    for (int h = 0; (1<<h) < l; h++) {
        for (int i = 0; i < l; i++) {
            suf_sort[i] = suffix_array[i] - (1<<h);
            if (suf_sort[i] < 0){
                suf_sort[i] += l;
            }
        }
        
        memset (cnt, 0, quantity_of_classes * sizeof(int));
        
        for (int i = 0; i < l; i++){
            cnt[classes[suf_sort[i]]]++;
        }
        for (int i = 1; i < quantity_of_classes; i++){
            cnt[i] += cnt[i - 1];
        }
        for (int i = l - 1; i >= 0; i--){
            suffix_array[--cnt[classes[suf_sort[i]]]] = suf_sort[i];
        }
        
        new_classes[suffix_array[0]] = 0;
        quantity_of_classes = 1;
        
        for (int i = 1; i < l; i++) {
            int mid1 = (suffix_array[i] + (1<<h)) % l,  mid2 = (suffix_array[i-1] + (1<<h)) % l;
            if (classes[suffix_array[i]] != classes[suffix_array[i-1]] || classes[mid1] != classes[mid2]){
                quantity_of_classes++;
            }
            new_classes[suffix_array[i]] = quantity_of_classes - 1;
        }
        
        memcpy (classes, new_classes, l * sizeof(int));
    }
    suffix_array = {suffix_array.begin() + 1, suffix_array.end()};
    return suffix_array;
}

std::string Get_K_Str(std::vector<int> lcp, std::vector<int> suff, std::string str, long long K, int str_len, int str1_len) {
    long long count = 0;
    int cur_min = str_len;
    
    int num_of_cur_suff = -1;  // = 1, if current suff from 1 str; = 2 if from 2 str
    int num_of_last_suff = -1;
    if (suff[0] > str1_len) {
        num_of_cur_suff = 2;
    } else {
        num_of_cur_suff = 1;
    }
    
    // going through lcp
    for (int i = 1; i < str_len; i++) {
        if (suff[i] > str1_len) {
            num_of_cur_suff = 2;
        } else {
            num_of_cur_suff = 1;
        }
        
        // in case there are common substr
        if (num_of_cur_suff != num_of_last_suff) {
            count += std::max(0, lcp[i - 1] - cur_min);
            cur_min = lcp[i - 1];
        } else {
            cur_min = std::min(cur_min, lcp[i - 1]);
        }
        num_of_last_suff = num_of_cur_suff;
        
        // если более чем на kм месте в лексикографически отсортированном списке
        if (count >= K) {
            long long countmoreKvalue = count - K;
            long long found_substr_len = lcp[i - 1] - countmoreKvalue;
            std::string result = "";
            for (int k = suff[i]; k < suff[i] + found_substr_len; k++) {
                result += str[k];
            }
            return result;
        }
    }
    
    return "-1";
}

int main() {
    //reading necessary information
    std::string s, s1, t;// строка
    std::ifstream in;
    std::cin >> s1 >> t;
    s = s1 + '$' + t + '#';
    int l = int(s.length()); // string length
    
    //bulding suffix array
    std::vector<int> suff;
    suff = Build_Suf_Array(s, l);
    
    //building lcp
    std::vector<int> lcp;
    lcp = Build_LCP(s, suff, l - 1);
    
    long long k;
    std::cin >> k;
    
    std::cout << Get_K_Str(lcp, suff, s, k, l, int(s1.length()));
    return 0;
}

