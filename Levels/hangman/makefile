all: hangman

hangman: main.o hangman.o 
	g++ main.o hangman.o -o hangman

main.o: main.cpp
	g++ -c main.cpp

hangman.o: hangman.cpp
	g++ -c hangman.cpp


clean:
	rm *o hangman