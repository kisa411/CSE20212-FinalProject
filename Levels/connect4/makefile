all: connectfour

connectfour: main.o C4Col.o C4Board.o
	g++ main.o C4Col.o C4Board.o -o connectfour

main.o: main.cpp
	g++ -c main.cpp

C4Col.o: C4Col.cpp
	g++ -c C4Col.cpp

C4Board.o: C4Board.cpp
	g++ -c C4Board.cpp

clean:
	rm *o connectfour