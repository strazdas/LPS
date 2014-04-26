//============================================================================
// Name        : comb_part_C.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <mpi.h>
#include <list>
#include <algorithm>
#include <time.h>
#include <unistd.h>
using namespace std;

#define BILLION  1000000000L;


int main(int argc, char *argv[]) {
    int rank;
    int procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct timespec start, stop;
    double duration;

    int j= 1;
    clock_gettime(CLOCK_REALTIME, &start);
    # pragma omp parallel for
    for (int i=0; i < 640; i++){
        for (int j=0; j < 1200000; j++){
            j *= 2; 
            j /= 2;
        }
            // usleep(10000);
    }
    clock_gettime(CLOCK_REALTIME, &stop);

    MPI_Finalize();


    duration = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;

    if (rank == 0) {
        printf("threads=%d ,  %f sec.\n", 2, duration);
    }

    return 0;
}
