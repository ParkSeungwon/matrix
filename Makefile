CFLAG = -std=c++11 -g -fmax-errors=3 
CC = g++
SRC = $(wildcard *.cc)
CPP = $(wildcard *.cpp)
EXE = $(patsubst %.cpp, %.x, $(CPP))
OBJ = $(patsubst %.cc, %.o, $(SRC))

all : $(OBJ) $(EXE) 

%.x : %.cpp $(OBJ)
	$(CC) $< -o $@ $(OBJ) $(CFLAG)

%.o : %.cc %.h
	$(CC) $< -c $(CFLAG)

clean :
	rm *.o *.x
