######################################################
# Args to be passed through CLI
######################################################

TYPE = 1
SIZE = 1000
TASK = 10
NP=14

######################################################
# Various constants and rules
######################################################

MPICH=/usr/local/mpich2-install/bin
CC = $(MPICH)/mpicc
RUN = $(MPICH)/mpirun

all: run

.c.o:
	$(CC) -c $<

build: main.c real.c
	@$(CC) main.c real.c -o output

copy: build
	@cp output /home/$(USER)
	@./cp-to-blades.sh /home/$(USER)/output

run: copy
	@(cd /home/$(USER); $(RUN) -np $(NP) output -p $(TYPE) -s $(SIZE) -b $(TASK))

tests: copy
	@(cd /home/$(USER); $(RUN) -np $(NP) output -t 1 -p $(TYPE) -b $(TASK))

run-sequential: build
	@./output -t 0 -p 0 -s $(SIZE)

tests-sequential: build
	@./output -t 1 -p 0

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
