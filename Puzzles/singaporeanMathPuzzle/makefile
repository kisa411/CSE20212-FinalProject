all: singapore

singapore: main.o singaporeanMathPuzzle.o 
	g++ main.o singaporeanMathPuzzle.o -o singapore

main.o: main.cpp
	g++ -c main.cpp

singaporeanMathPuzzle.o: singaporeanMathPuzzle.cpp
	g++ -c singaporeanMathPuzzle.cpp


clean:
	rm *o singapore