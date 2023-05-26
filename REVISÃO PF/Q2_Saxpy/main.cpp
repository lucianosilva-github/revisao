#include <omp.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
#include <vector>

int main(){

    // Read N and c
    int N, c;
    std::cin >> N >> c;

    // Set num_threads for experiment
    omp_set_num_threads(8);

    // Random seed generator
    std::random_device generator;

    // Random engine for each thread
    std::vector<std::default_random_engine> engines;
    for (int i = 0, n = 8; i < n; i++) {
        engines.emplace_back(std::default_random_engine(generator()));
    }
    std::uniform_int_distribution<int> num_distro(0,100);


    // Parallel for to generate random numbers in array
    int a[N];
    int b[N];
    #pragma omp parallel for
    for(int i = 0; i<N; i++){
        std::default_random_engine& g = engines[omp_get_thread_num()];
        a[i] = num_distro(g);
        b[i] = num_distro(g);
    }

    // // Sanity check arr
    // std::cout << "First 10 elements of array:" << std::endl; 
    // for(int i = 0; i<10; i++){
    //     std::cout << "(" << a[i] << "," << b[i] << ") ";
    // }
    // std::cout << std::endl;

    int Y[N];
    // Parallel saxpy
    #pragma omp parallel for shared(Y)
    for (int i = 0; i<N; i++){
        Y[i] = a[i]*c + b[i];
    }

    // Sanity check arr
    // std::cout << "First 3 elements of output:" << std::endl; 
    // for(int i = 0; i<3; i++){
    //     std::cout << c << " * " << a[i] << " + " << b[i] << " = " << Y[i] << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}