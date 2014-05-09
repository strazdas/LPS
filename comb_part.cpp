#include <stdio.h>
#include <list>
#include <algorithm>
#include <time.h>
using namespace std;

#define BILLION  1000000000L;


int main(int argc, char *argv[]) {
    struct timespec start, stop;
    double duration;
    int n = 10;

    int number_of_simpleces = 1;
    for (int i = 1; i <= n; i++) {
	number_of_simpleces *= i;
    }

    int teta[n];
    for (int i=0; i < n; i++){
        teta[i] = i;
    }
    // teta = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    clock_gettime(CLOCK_REALTIME, &start);

    do {
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

    } while (std::next_permutation(teta, teta+n));


    clock_gettime(CLOCK_REALTIME, &stop);
    duration = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;

    printf("0, %f\n", duration);      // (end - start)/double(CLOCKS_PER_SEC));

    return 0;
}
