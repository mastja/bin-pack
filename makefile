# macro tells which compiler to use
CC = g++

# macro says using c++11 standard
CFLAGS = -std=c++11 -c

# run "make all" to run binPack
all: binPack

# make the binPack program
bin: binPack.o
	$(CC) binPack.o -o pack

binPack.o:
	$(CC) $(CFLAGS) binPack.cpp

clean:
	rm *.o
	rm binPack