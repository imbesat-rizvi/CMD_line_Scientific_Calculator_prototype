CC = g++
EXEC = calc.out

all: main.o Calculator.o
	$(CC) -o $(EXEC) main.o Calculator.o

main.o: main.cpp
	$(CC) -c main.cpp

Calculator.o: Calculator.h Calculator.cpp
	$(CC) -c Calculator.cpp

clean:
	rm *.o *.out
