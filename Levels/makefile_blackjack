all: cardDeck

cardDeck: main.o cardDeck.o
	g++ main.o cardDeck.o -o cardDeck

main.o: main.cpp
	g++ -c main.cpp

cardDeck.o: cardDeck.cpp
	g++ -c cardDeck.cpp

clean:
	rm -f *o cardDeck