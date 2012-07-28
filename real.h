#ifndef REAL_H
#define REAL_H

#define TASK_SIZE 3
#define TASK_TAG 0
#define RESULT_TAG 1
#define RANDOM_REAL_TAG 2
#define PROBLEM_SIZE 1000

// 0 = Sequential
// 1 = Data parallelism
// 2 = Bag of tasks
int parallelismType;

int size;

// Displays informations on CLI.
int verbose;

// Number of the test to be executed.
// Else :  -1 = no test, 0 = all tests.
int tests;

// Values set by MPI.
int processorId;
int nProcessors;

typedef struct {
	int* figures;
	int length;
	int exponent;
} real;

// The result of processing will be written in this var.
real result;

void parseOptions(int argc, char *argv[]);
real randomReal();
void process(real first, real second);
real realFromString(char* number);
int intFromChar(char c);
void sequentialMultiplication(real first, real second);
int coefficient(int index, real first, real second);
real normalize(real myReal);
void dataParallelMultiplication( real first, real second);
void tasksBagParallelMultiplication(real first, real second);
void printReal(real myReal);

#endif
