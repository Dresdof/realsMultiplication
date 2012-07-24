#include <ctype.h>
#include <unistd.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "real.h"

void parseOptions(int argc, char *argv[]) {

	// Generic char intended to get the getopt return value;
	char c;
	opterr = 0;

	while ((c = getopt (argc, argv, "p:l:t:")) != -1) {
		switch (c) {
			case 'p':
				parallelismType = atoi(optarg);
				break;
			case 'l':
				length = atoi(optarg);
				break;
			case 't':
				testsExecuted = atoi(optarg);
				break;

			case '?':
				if (optopt == 'p' || optopt == 't' || optopt == 'l')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				exit(1);

			default:
				exit(1);
		}
	}
	if (parallelismType < 0 || parallelismType > 2) 
		parallelismType = 0;

	if (length < 0) 
		length = DEFAULT_LENGTH;

}
