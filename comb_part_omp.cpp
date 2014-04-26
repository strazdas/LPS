#include <stdio.h>
#include <omp.h>
#include <list>
// #include <algorithm>
#include <time.h>
using namespace std;

#define BILLION  1000000000L;


int main(int argc, char *argv[]) {
	int n = 10;
    int threads = 24;
	omp_set_num_threads(threads);
    int procs = omp_get_num_procs();

	double total_clocks;
	clock_t start_clock = clock();
	clock_t end_clock;

	struct timespec start, stop;
	double duration;


	int number_of_simpleces = 1;
	for (int i = 1; i <= n; i++) {
		number_of_simpleces *= i;
	}

	clock_gettime(CLOCK_REALTIME, &start);
	// int triangles[number_of_simpleces][n + 1][n];


	// Lygiagrecios programos realizacija

//	  teta = []
//    for j in range(0, n):
//        teta.append(j)
//
//    c = 1
//    for j in range(2, n+1):
//        c *= j - 1
//        i = j - 1 - (k/c) % j
//        tmp = teta[j-1]
//        teta[j-1] = teta[i]
//        teta[i] = tmp

	#pragma omp parallel for //shared(triangles)
	for (int simplex=0; simplex < number_of_simpleces; simplex++) {
		// Get permutation from simplex index.

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

        int triangle[n+1][n];
		// std::next_permutation(teta, teta + n);
	    for (int k = 0; k < n; k++) {
			// triangles[simplex][0][k] = 0;
	    	triangle[0][k] = 0;
		};

	    // printf("Simplex %d\n", simplex);
		for (int vertex=0; vertex < n; vertex++) {
			for (int j = 0; j < n + 1; j++) {
				// triangles[simplex][vertex + 1][j] = triangles[simplex][vertex][j];
				triangle[vertex + 1][j] = triangle[vertex][j];
			};

			// triangles[simplex][vertex + 1][teta[vertex]] = 1;
			triangle[vertex + 1][teta[vertex]] = 1;
		}

	}

//		for (int l = 0; l < number_of_simpleces; l++) {
//			// simplex
//			for (int i = 0; i < n + 1; i++) {
//				printf("(");
//				// vertex
//				for (int vertex = 0; vertex < n; vertex++) {
//					// coordinate
//					printf("%d ", triangles[l][i][vertex]);
//				}
//				printf(") ");
//			}
//			printf("\n");
//		}


	end_clock = clock();
	clock_gettime(CLOCK_REALTIME, &stop);
    duration = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;

    // FILE *file;
    // file = fopen("results", "a+");

    // fprintf(file, "n=%d, proc=%d, threads=%d, exec.time: %f secs., clokcs: %f\n", n, procs, threads, duration, (end_clock - start_clock)/double(CLOCKS_PER_SEC));
    // fclose(file);

	printf("%d, %f\n", threads, duration); //(end - start)/double(CLOCKS_PER_SEC));

	return 0;
}
