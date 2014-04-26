//============================================================================
// Name        : comb_part_C.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <omp.h>
#include <list>
#include <algorithm>
#include <time.h>
#include <unistd.h>
using namespace std;

#define BILLION  1000000000L;


int main(int argc, char *argv[]) {
    int threads = 24;
    omp_set_num_threads(threads);
    int procs = omp_get_num_procs();

    struct timespec start, stop;
    double duration;

    int j= 1;
    clock_gettime(CLOCK_REALTIME, &start);

    # pragma omp parallel for
    for (int i=0; i < 640; i++){
        for (int j=0; j < 600000; j++){
            j *= 2; 
            j /= 2;
        }
            // usleep(10000);
    }
    clock_gettime(CLOCK_REALTIME, &stop);


    duration = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;

    printf("%d, %f\n", threads, duration);

    return 0;
}
