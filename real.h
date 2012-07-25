#ifndef REAL_H
#define REAL_H

#define DEFAULT_LENGTH 500;

// 0 = Sequential
// 1 = Data parallelism
// 2 = Tasks bag
int parallelismType;
int length;

// Number of the test to be executed.
// Else :  -1 = no test, 0 = all tests.
int testsExecuted;

typedef struct {
	int* figures;
	int length;
	int exponent;
} real;

real nan;

void parseOptions(int argc, char *argv[]);
real realFromString(char* number);
int intFromChar(char c);
real sequentialMultiplication(real first, real second);
int coefficient(int index, real first, real second);
real normalize(real myReal);


#endif
