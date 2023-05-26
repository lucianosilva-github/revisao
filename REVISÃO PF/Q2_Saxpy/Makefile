gpu: main.cu
	nvcc -arch=sm_70 -std=c++14 main.cu -o main_gpu

cpu: main.cpp
	g++ -Og -Wall -fopenmp main.cpp -o main_cpu

run: cpu gpu
	./main_cpu
	./main_gpu