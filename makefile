
######################################################
# Args to be passed through CLI
######################################################

TYPE = 0
VERBOSE = 1
TESTS = 0
FIRST = 
SECOND =

ifeq "$(VERBOSE)" "1"
	OPTS = -v -p $(TYPE) -f $(FIRST) -s $(SECOND)
else
	OPTS = -p $(TYPE) -f $(FIRST) -s $(SECOND)
endif


######################################################
# Various constants and rules
######################################################

# Number of processors
NP=8

MPICH=/usr/local/mpich2-install/bin
CC = $(MPICH)/mpicc
RUN = $(MPICH)/mpirun

all: run

.c.o:
	$(CC) -c $<

build: main.c real.c
	$(CC) main.c real.c -o output

copy: build
	@cp output /home/$(USER)
	@./cp-to-blades.sh /home/$(USER)/output

run: copy
	@(cd /home/$(USER); $(RUN) -np $(NP) output $(OPTS))

run-sequential: build
	./output -t 0 -f $(FIRST) -s $(SECOND)

run-tests: copy
	(cd /home/$(USER); $(RUN) -np $(NP) output -t $(TESTS) $(OPTS))

mpdboot:
	@(rm -f .mpdboot*)
	@(cp mpd.hosts /home/$(USER))
	@./activate-mpdboot.sh $(NP) mpd.hosts

clean:
	@rm -f $(TMPFILES)
	@rm -f /home/$(USER)/output
	@rm -f /home/$(USER)/unemachine.txt
	@rm -f /home/$(USER)/deuxmachines.txt
	@rm -f *~
	@rm -f .mpdboot* .copy*
