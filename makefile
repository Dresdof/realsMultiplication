
MPICH=/usr/local/mpich2-install/bin
CC = $(MPICH)/mpicc
RUN = $(MPICH)/mpirun

all: build run


.c.o:
	$(CC) -c $<

build: main.c real.c
	$(CC) main.c real.c -o output

run:
	./output
