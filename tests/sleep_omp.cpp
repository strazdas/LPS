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


	clock_gettime(CLOCK_REALTIME, &start);
    # pragma omp parallel for
	for (int i=0; i < 640; i++){
            usleep(10000);
	}
	clock_gettime(CLOCK_REALTIME, &stop);

	duration = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    printf("threads=%d ,  %f sec.\n", threads, duration);
	return 0;
}
