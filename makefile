
######################################################
# Args to be passed through CLI
######################################################

TYPE=0

######################################################
# Various constants and rules
######################################################
# Prevents errors during tests to abort execution
.IGNORE:

# Number of processors
NP=8

MPICH=/usr/local/mpich2-install/bin
CC = $(MPICH)/mpicc
RUN = $(MPICH)/mpirun

all: build copy run

.c.o:
	$(CC) -c $<

build: main.c real.c
	$(CC) main.c real.c -o output

copy: build
	@cp output /home/$(USER)
	@./cp-to-blades.sh /home/$(USER)/output

run: build copy mpdboot
	@(cd /home/$(USER); $(RUN) -np $(NP) output -t $(TYPE))

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
