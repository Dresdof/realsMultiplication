#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "real.h"
#include "parseoptions.h"

// Signification of the values : 
//	int[0] type of parallelism
//	int[1] length of the real number to be generated
//	int[2] test to be executed (0 = all)
int* parseOptions(int argc, char *argv[]) {

	// Generic char intended to get the getopt return value;
	char c;

	int values[3];

	int i;
	for(i = 0; i < 3; i++) 
		values[i] = -1;
	
	opterr = 0;

	while ((c = getopt (argc, argv, "r:c:g:f:t:")) != -1) {
		switch (c) {
			case 'p':
				values[0] = atoi(optarg);
				break;
			case 'l':
				values[1] = atoi(optarg);
				break;
			case 't':
				values[2] = atoi(optarg);
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
	return values;
}
