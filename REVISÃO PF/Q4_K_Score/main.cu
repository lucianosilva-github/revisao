#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>
#include <thrust/execution_policy.h>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstdio>

#define MATCH 2
#define MISMATCH -1
#define GAP -1
#define SHOW_REPORT false
#define SHOW_MATRIX false

struct PrintSeq {
    __host__ __device__
    int operator()(const char y){
        printf("%c", y);
        return y;
    }
};

int main(){

    // Inputs
    int len_a, len_b;
    std::cin >> len_a >> len_b;
    std::string a, b;
    std::cin >> a >> b;
    std::string big, small;

    if(len_a > len_b){
        big = a;
        small = b;
    } else {
        big = b;
        small = a;
    }

    // Send string to gpu vector    
    thrust::device_vector<char> big_str(big.length());
    for(int i = 0; i < big.length(); i++){
        big_str[i] = big[i];
    }

    // Send string to gpu vector    
    thrust::device_vector<char> small_str(small.length());
    for(int i = 0; i < small.length(); i++){
        small_str[i] = small[i];
    }

    

    return 0;
}