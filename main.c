#include <mpi.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	double mpi_time;
	clock_t clock_time;

	if (parallelismType != 0) {
		MPI_Init( &argc, &argv );

		MPI_Comm_rank (MPI_COMM_WORLD, &processorId);
		MPI_Comm_size (MPI_COMM_WORLD, & nProcessors);
	}

		if(processorId == 0 || parallelismType == 0) {
			printf("High precision reals multiplication.\n Type of execution: ");
			switch(parallelismType) {
				case 0:
					printf("Sequential.\n");
					break;
				case 1:
					printf("Data parallelism.\n");
					break;
				case 2:
					printf("Bag of tasks.\n");
					break;
			}
		}

	if(!tests) {
		real firstReal = randomReal();
		real secondReal = randomReal();

		if(parallelismType != 0)
			mpi_time = -MPI_Wtime();
		else
			clock_time = -clock();

		process(firstReal, secondReal);

		if(parallelismType != 0)
			mpi_time += MPI_Wtime();
		else
			clock_time += clock();
	}
	else {
		if(processorId == 0) printf("Tests execution: \n");
		// Test 1
		real first = stringToReal("0.1337E+4");
		real second = stringToReal("0.2443E+5");
		real expected = stringToReal("0.3266291E+8");
		runTest(first, second, expected);

		// Test 2
		first = stringToReal("0.35154586548E+7");
		second = stringToReal("0.244314231E+9");
		expected = stringToReal("0.8588765778597564588E+15");
		runTest(first, second, expected);

		// Test 3
		first = stringToReal("0.6546543E+7");
		second = stringToReal("0.78778234E-9");
		expected = stringToReal("0.515725096345062E-2");
		runTest(first, second, expected);
	}

	float time;

	if (parallelismType != 0) {
		time = mpi_time;
		MPI_Finalize();
	}
	else time = (float)clock_time / (float)CLOCKS_PER_SEC;
	
	if( (processorId == 0 || parallelismType == 0) && !tests) {
		printf("Execution finished.\n Time for a problem of size %i: %1.3fs.\n", problemSize, time);
		result = normalize(result);
	}
  return 0;
}
