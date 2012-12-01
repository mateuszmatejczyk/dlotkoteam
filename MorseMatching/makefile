#cel: od czego zalezy cel
#	jak to zrobic

CC = g++
FLAGS = -O2 -Wall

SRC = $(wildcard *.cpp)
HFILES = $(wildcard *.h)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
#LIBS = -lgmpxx -lgmp

main: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o main

%.o: %.cpp $(HFILES)
	$(CC) $(FLAGS) -c $*.cpp -o $*.o
