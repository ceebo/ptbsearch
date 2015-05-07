CC = gcc
CFLAGS = -O3
NEEDED = gen.o rmo.o file.o analyze.o components.o lifelist.o gen2x2.o

all: ptb2 survive

ptb2: ptb2.o ptbsearch2.o $(NEEDED)
	$(CC) $(CFLAGS) -o ptb2 ptb2.o ptbsearch2.o $(NEEDED)

survive:	survive.o $(NEEDED)
	$(CC) $(CFLAGS) -o survive survive.o $(NEEDED)