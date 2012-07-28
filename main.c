#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	parallelismType = 2;
	verbose = 1;

	if (parallelismType != 0) {
		MPI_Init( &argc, &argv );

		MPI_Comm_rank (MPI_COMM_WORLD, &processorId);
		MPI_Comm_size (MPI_COMM_WORLD, & nProcessors);

		if(processorId == 0 && verbose) 
			switch(parallelismType) {
				case 1:
					printf("Data parallelisme execution.\n");
					break;

				case 2:
					printf("Bag of tasks execution.\n");
					break;
			}
	} else if(verbose)
		printf("Sequential execution.\n");

	real firstReal = randomReal();
	real secondReal = randomReal();

	printf("%i. firstReal.length: %i.\n", processorId, firstReal.length);
	printf("%i. secondReal.length: %i.\n", processorId, secondReal.length);

	process(firstReal, secondReal);
	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
