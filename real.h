#ifndef REAL_H
#define REAL_H

// 0 = Sequential
// 1 = Data parallelism
// 2 = Tasks bag
int parallelismType;

// Number of the test to be executed.
// Else :  -1 = no test, 0 = all tests.
int tests;

// Numbers to be multiplicated.
char* first;
char* second;

// Displays informations on CLI.
int verbose;

typedef struct {
	int* figures;
	int length;
	int exponent;
} real;

real nan;

void parseOptions(int argc, char *argv[]);
real process(real first, real second);
real realFromString(char* number);
int intFromChar(char c);
real sequentialMultiplication(real first, real second);
int coefficient(int index, real first, real second);
real normalize(real myReal);
real dataParallelMultiplication( real first, real second);
real tasksBagParallelMultiplication(real first, real second);

#endif
