#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "real.h"

int main ( int argc, char *argv[]) {
	
	parseOptions(argc, argv);

	real myReal = realFromString("0.9845E+3");
	real myOtherReal = realFromString("0.3698E+3");

	real result = normalize(sequentialMultiplication(myReal, myOtherReal));

	int i;
	printf("Result: ");
	for (i = 0; i < result.length; i++)
		printf("•%i", result.figures[i]);
	printf(" E %i, L: %i\n", result.exponent, result.length);

	if (parallelismType != 0)
		MPI_Init( &argc, &argv );
	
	if (parallelismType != 0)
		MPI_Finalize();

  return 0;
}
