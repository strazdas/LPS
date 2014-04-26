#include <stdio.h>
#include <mpi.h>
#include <list>
#include <time.h>
using namespace std;

#define BILLION  1000000000L;


int main(int argc, char *argv[]) {
    int n = 10;

    double total_clocks;
    clock_t start_clock = clock();
    clock_t end_clock;

    struct timespec start, stop;
    double duration;

    int number_of_simpleces = 1;
    for (int i = 1; i <= n; i++) {
            number_of_simpleces *= i;
    }

    // Should collect the triangles:
    // int triangles[number_of_simpleces][n + 1][n];
    int procs, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);


    clock_gettime(CLOCK_REALTIME, &start);
    //*****   Lygiagrečios programos realizacija   *****//
    int from = rank * (number_of_simpleces / procs);
    int till;
    if (rank == procs -1){
        till = number_of_simpleces;
    } else {
        till = (rank+1) * (number_of_simpleces / procs);
    };
    // printf("rank= %d, from= %d, till= %d", rank, from, till);

    for (int simplex=from; simplex < till; simplex++) {
        //*****   Generate permutation from simplex index   *****
        int teta[n];
	for (int i=0; i<n; i++) teta[i] = i;
        int c = 1;
        for (int j=2; j<=n; j++){
            c *= j-1;
            int i = j - 1 - (simplex/c) % j;
            int tmp = teta[j-1];
            teta[j-1] = teta[i];
            teta[i] = tmp;
        }

        //*****   Generate simplex from permutation   *****
        int triangle[n+1][n];
	for (int k = 0; k < n; k++) {
	    triangle[0][k] = 0;
	};

        for (int vertex=0; vertex < n; vertex++) {
	    for (int j = 0; j < n + 1; j++) {
                triangle[vertex + 1][j] = triangle[vertex][j];
	    };
	    triangle[vertex + 1][teta[vertex]] = 1;
	}
        //*****   Save the triangle to the global scope variable   *****
    }
    clock_gettime(CLOCK_REALTIME, &stop);

    //*****  Print all the triangles   *****
    //  for (int l = 0; l < number_of_simpleces; l++) {
    //      // simplex
    //      for (int i = 0; i < n + 1; i++) {
    //          printf("(");
    //          // vertex
    //          for (int vertex = 0; vertex < n; vertex++) {
    //          // coordinate
    //              printf("%d ", triangles[l][i][vertex]);
    //          }
    //          printf(") ");
    //      }
    //      printf("\n");
    //  }


    // printf("Process %d on %s out of %d\n", rank, processor_name, procs);
    end_clock = clock();

    MPI_Finalize();
    if (rank == 0) {

        // end_clock = clock();
        // clock_gettime(CLOCK_REALTIME, &stop);
        duration = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;

        // FILE *file;
        // file = fopen("results", "a+");

        // fprintf(file, "n=%d, threads=%d, exec.time: %f secs., clokcs: %f\n", n, procs, duration, (end_clock - start_clock)/double(CLOCKS_PER_SEC));
        // fclose(file);

        printf("Excecution time: %f\n", duration); //(end - start)/double(CLOCKS_PER_SEC));
    };
    return 0;
}
