#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	first = "0.9845E+3";
	second = "0.3698E+3";

	real firstReal = realFromString(first);
	real secondReal = realFromString(second);

	parallelismType = 1;
	verbose = 1;

	real result = normalize(process(firstReal, secondReal));


	int i;
	printf("Result: ");
	for (i = 0; i < result.length; i++)
		printf("%i", result.figures[i]);
	printf(" E %i, L: %i\n", result.exponent, result.length);

	if (parallelismType != 0)
		MPI_Init( &argc, &argv );
	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
