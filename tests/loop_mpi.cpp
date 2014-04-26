//============================================================================
// Name        : comb_part_C.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <list>
#include <algorithm>
#include <time.h>
#include <unistd.h>
#include <mpi.h>
using namespace std;

#define BILLION  1000000000L;



int main(int argc, char *argv[]) {
    // int threads = 24;
    // omp_set_num_threads(threads);
    // int procs = omp_get_num_procs();

    int rank;
    int procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // MPI_Get_processor_name(processor_name, &namelen);

    struct timespec start, stop;
    double duration;


    int j= 1;
    clock_gettime(CLOCK_REALTIME, &start);
    // Get the number of the rank and paralelize .
    int total_loops = 3628800; // 640 * 5670;
    
    int from = rank * (total_loops / procs);
    int till;
    if (rank == procs -1){
        till = total_loops;
    } else {
        till = (rank+1) * (total_loops / procs);
    };
    
    // # pragma omp parallel for
    for (int i=from; i < till; i++){
        for (int j=0; j < 212 ; j++){
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
