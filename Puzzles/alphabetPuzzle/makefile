all: alphabet

alphabet: main.o alphabetPuzzle.o 
	g++ main.o alphabetPuzzle.o -o alphabet

main.o: main.cpp
	g++ -c main.cpp

alphabetPuzzle.o: alphabetPuzzle.cpp
	g++ -c alphabetPuzzle.cpp


clean:
	rm *o alphabet