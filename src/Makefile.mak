CPP    = g++
RM     = rm -f
OBJS   = main.o

LIBS   =
CFLAGS =

.PHONY: ../../clustering_bio_sequences.exe clean clean-after

all: ../../clustering_bio_sequences.exe

clean:
	$(RM) $(OBJS) ../../clustering_bio_sequences.exe

clean-after:
	$(RM) $(OBJS)

../../clustering_bio_sequences.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.cpp tests.h kmeans.h fasta_file.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

