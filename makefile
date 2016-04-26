FLAGS= -std=c++0x -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libstdc++ -O1
all: NomNom

NomNom: main.o puzzle.o puzzleElement.o alphabetPuzzle.o Rivercrossing.o hangman.o Blackjack.o cryptography.o singaporePuzzle.o opening.o ending.o CardDeck.o sdl_win_wrap.o texture.o player.o
	g++ $^ $(FLAGS) -o $@
puzzle.o: Levels/sudoku/puzzle.cpp
	g++ -c $^ $(FLAGS)

puzzleElement.o: Levels/sudoku/puzzleElement.cpp
	g++ -c $^ $(FLAGS)

alphabetPuzzle.o: Puzzles/alphabet/alphabetPuzzle.cpp
	g++ -c $^ $(FLAGS)

Rivercrossing.o: Puzzles/rivercrossingPuzzle/Rivercrossing.cpp
	g++ -c $^ $(FLAGS)

hangman.o: Levels/hangman/hangman.cpp
	g++ -c $^ $(FLAGS)

cryptography.o: Puzzles/cryptography/cryptography.cpp
	g++ -c $^ $(FLAGS)

singaporePuzzle.o: Puzzles/singapore/singaporePuzzle.cpp
	g++ -c $^ $(FLAGS)

opening.o: opening/opening.cpp
	g++ -c $^ $(FLAGS)

ending.o: ending/ending.cpp
	g++ -c $^ $(FLAGS)

#Blackjack.o: Levels/blackjack/Blackjack.cpp
	#g++ -c $^ $(FLAGS)

CardDeck.o: Levels/blackjack/CardDeck.cpp
	g++ -c $^ $(FLAGS)

sdl_win_wrap.o: sharedClasses/sdl_win_wrap.cpp
	g++ -c $^ $(FLAGS)

texture.o: sharedClasses/texture.cpp
	g++ -c $^ $(FLAGS)

Blackjack.o: Levels/blackjack/Blackjack.cpp
	g++ -c $^ $(FLAGS)
player.o: player.cpp
	g++ -c $^ $(FLAGS)

main.o: main.cpp
	g++ -c $^ $(FLAGS)

clean:
	rm *.o NomNom






