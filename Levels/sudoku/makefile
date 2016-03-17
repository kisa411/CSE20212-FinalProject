all: puzzle

puzzle: main.o 
	g++ main.o -o puzzle

main.o: main.cpp puzzle.h
	g++ -c main.cpp

clean:
	rm -f *o puzzle