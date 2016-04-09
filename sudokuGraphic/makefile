all: test

test: main.cpp puzzle.cpp sdl_win_wrap.cpp texture.cpp puzzleElement.cpp
	g++ $^ -o test -g -gdwarf-2 -lSDL2_image -lSDL2_ttf

clean:
	rm test
