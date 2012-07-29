#ifndef REAL_H
#define REAL_H

#define DEFAULT_TASK_SIZE 10
#define DEFAULT_PROBLEM_SIZE 1000
// Tags for MPI messages
#define TASK_TAG 0
#define RESULT_TAG 1
#define RANDOM_REAL_TAG 2

// 0 = Sequential
// 1 = Data parallelism
// 2 = Bag of tasks
int parallelismType;

int problemSize;
int taskSize;

// Bool: tests will be executed or not.
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
int equals(real first, real second);
real stringToReal(char* number);
void sequentialMultiplication(real first, real second);
int coefficient(int index, real first, real second);
real normalize(real myReal);
void dataParallelMultiplication( real first, real second);
void tasksBagParallelMultiplication(real first, real second);
char* realToString(real myReal);

#endif
