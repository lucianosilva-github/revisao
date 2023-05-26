#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/random.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <random>

#define N 10000000

struct rng_gpu {
    __device__ __host__
    double operator() (int seed) {
        thrust::default_random_engine en_gpu((seed*23778956)%151368);
        thrust::uniform_real_distribution<double> d(0,1);
        return d(en_gpu);
    }
};

struct add_squares
{
    __host__ __device__
    double operator()(const double& x, const double& y) {
        return x*x + y*y;
    }
};

struct greater_than_one {
    __device__ __host__
    double operator() (double num) {
        return num <= 1 ? 1 : 0;
    }
};

int main(){

    // Initialize Vectors using random number generation
    thrust::device_vector<double> X(N);
    thrust::device_vector<double> Y(N);
    thrust::transform(thrust::make_counting_iterator(0), thrust::make_counting_iterator(N), X.begin(), rng_gpu());
    thrust::transform(thrust::make_counting_iterator(N), thrust::make_counting_iterator(2*N), Y.begin(), rng_gpu());

    // Apply sum of squares transform
    thrust::transform(X.begin(), X.end(), Y.begin(), X.begin(), add_squares());

    // Use transform reduce to count occorruences of circle hit 
    double pi = 4.0*thrust::transform_reduce(X.begin(), X.end(), greater_than_one(), 0, thrust::plus<double>())/(double)N;

    // Result is pi!
    std::cout << "Pi is: " << pi << std::endl;

    return 0;
}