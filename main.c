#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"
#include "parseoptions.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	if (parallelismType != 0)
		MPI_Init( &argc, &argv );
	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
