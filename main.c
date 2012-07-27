#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	first = "0.98456576E+3";
	second = "0.36981321E+3";

	real firstReal = realFromString(first);
	real secondReal = realFromString(second);

	parallelismType = 2;
	verbose = 1;


	if (parallelismType != 0)
		MPI_Init( &argc, &argv );

	real result = normalize(process(firstReal, secondReal));


	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
