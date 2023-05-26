#include <omp.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
#include <vector>

// #define N 10
// #define NUM_THREADS 2

int main(){

    // Read N and NUM_THREADS
    int NUM_THREADS, N;
    std::cin >> N >> NUM_THREADS;

    // Set num_threads for experiment
    omp_set_num_threads(NUM_THREADS);

    // Random seed generator
    std::random_device generator;

    // Random engine for each thread
    std::vector<std::default_random_engine> engines;
    for (int i = 0, n = NUM_THREADS; i < n; i++) {

        engines.emplace_back(std::default_random_engine(generator()));
    }
    std::uniform_int_distribution<int> num_distro(1,999);

    
    // Parallel for to generate random numbers in array
    int arr[N];
    #pragma omp parallel for
    for(int i = 0; i<N; i++){
        std::default_random_engine& g = engines[omp_get_thread_num()];
        arr[i] = num_distro(g);
    }

    // Sanity check arr
    // std::cout << "First 10 elements of array:" << std::endl; 
    // for(int i = 0; i<10; i++){
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    // Parallel sum
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i<N; i++){
        sum += arr[i];
    }
    const float mean = ((float)sum) / ((float)N);

    // Parallel variance
    float variance = 0;
    #pragma omp parallel for reduction(+:variance)
    for (int i = 0; i<N; i++){
        float dif = arr[i] - mean;
        variance += dif*dif;
    }

    const float stddev = std::pow(variance/N, 0.5);

    // Output
    // std::cout << "Mean: " << mean;
    // std::cout << " Standard Deviation: " << stddev << std::endl;
    return 0;
}