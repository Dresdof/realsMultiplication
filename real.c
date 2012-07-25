#include <ctype.h>
#include <unistd.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
					printf ("Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					printf ("Unknown option `-%c'.\n", optopt);
				else
					printf ("Unknown option character `\\x%x'.\n", optopt);
				exit(1);

			default:
				exit(1);
		}
	}

	if (parallelismType < 0 || parallelismType > 2) 
		parallelismType = 0;

	if (length < 0) 
		length = DEFAULT_LENGTH;

	nan.figures = malloc(sizeof(int));
	if(nan.figures == NULL) exit(1);
	nan.length = 1;
	nan.exponent = -1;
}

int charToInt(char c) {
	assert(c >= '0' && c <= '9');
	return atoi(&c);
}

real realFromString(char* number) {
	real myReal = nan;
	int length = strlen(number);

	int position = 0;
	assert(position < length - 1 || number[position] == '0');

	position++;
	assert(position < length - 1 || number[position] == '.');

	position++;
	myReal.length = 0;

	// First loop to determine the number of figures.
	while (number[position] != 'E' && position < (length - 1)) {
		myReal.length++;
		position++;
	}

	myReal.figures = malloc(myReal.length * sizeof(int));
	if (myReal.figures == NULL) exit(1);

	int i;
	// Second loop to affect the figures.
	for(i = 0; i < myReal.length; i++)
		myReal.figures[i] = charToInt(number[i + 2]);

	assert(number[position] == 'E');
	position++;

	assert( (position < length) && (number[position] == '+' || number[position] == '-') );
	int positive = number[position] == '+';

	position++;
	assert(position < length);

	myReal.exponent = 0;


	for(i = position; i < length; i++)
		myReal.exponent = myReal.exponent * 10 + charToInt(number[i]);

	if (positive != 1) myReal.exponent = -myReal.exponent;


	return myReal;
}

real sequentialMultiplication(real first, real second) {

	real result;
	result.length = first.length + second.length - 1;

	result.figures = malloc(result.length * sizeof(int));
	if(result.figures == NULL) exit(1);

	int i;
	for (i = 0; i < result.length; i++)
		result.figures[i] = coefficient(i, first, second);

	result.exponent = first.exponent + second.exponent - 1;

	return result;
}

int coefficient(int index, real first, real second) {

	int i, result = 0;
	for (i = 0; i < first.length; i++) {
		int j;
		for (j = 0; j < second.length; j++)
			if(i + j - 1 == index - 1) 
				result += first.figures[i] * second.figures[j];
	}

	return result;
}

real normalize(real myReal) {
	//if (myReal == nan || isNormalized(myReal)) return myReal;

	real normalizedReal;

	normalizedReal.exponent = myReal.exponent;

	// Determine the number of figures needed
	int i, increment = 0, carryOver = 0;
	for (i = myReal.length - 1; i >= 0; i--) {
		carryOver = (myReal.figures[i] + carryOver) / 10;
		increment++;
	}

	while (carryOver > 0) {
		increment++;
		carryOver /= 10;
	}

	// Create the real with the good number of figures
	normalizedReal.figures = malloc(increment * sizeof(int));
	normalizedReal.length = increment;
	carryOver = 0;

	int k = myReal.length - 1;

	for(i = increment - 1; i >= 0; i--) {
		int value;

		if(k >= 0)
			value = myReal.figures[k] + carryOver;
		else {
			value = carryOver;
			if (value > 0) 
				normalizedReal.exponent++;
		}
		normalizedReal.figures[i] = value % 10;
		carryOver = value / 10;
		k--;
	}

	int lastNonZero = normalizedReal.length - 1;

	while (lastNonZero >= 0 && normalizedReal.figures[lastNonZero] == 0)
		lastNonZero--;

	lastNonZero = lastNonZero > 0 ? lastNonZero : 0;

	if (lastNonZero < normalizedReal.length - 1) {

		int* array = malloc ((lastNonZero + 1) * sizeof(int));

		for (i = 0; i <= lastNonZero; i++)
			array[i] = normalizedReal.figures[i];

		free(normalizedReal.figures);
		normalizedReal.figures = array;
		normalizedReal.length = lastNonZero + 1;
	}

	int firstNonZero = 0;

	while (firstNonZero < normalizedReal.length && normalizedReal.figures[firstNonZero] == 0)
		firstNonZero++;

	firstNonZero = firstNonZero < normalizedReal.length ? firstNonZero : normalizedReal.length;

	if (firstNonZero > 0) {
		int* array = malloc ( (normalizedReal.length - firstNonZero + 1) * sizeof(int));
		int i;
		for (i = firstNonZero; i < normalizedReal.length; i++)
			array[i] = normalizedReal.figures[i];

		free(normalizedReal.figures);
		normalizedReal.figures = array;
		normalizedReal.length -= firstNonZero;
	}

	if (normalizedReal.length == 1 && normalizedReal.figures[0] == 0)
		normalizedReal.exponent = 0;

	return normalizedReal;
}

