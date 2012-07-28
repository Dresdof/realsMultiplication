#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	first = "0.576626662543432144232E+3";
	second = "0.369834432432442351321E+3";

	real firstReal = realFromString(first);
	real secondReal = realFromString(second);

	parallelismType = 2;
	verbose = 1;

	if (parallelismType != 0)
		MPI_Init( &argc, &argv );

	process(firstReal, secondReal);
	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
