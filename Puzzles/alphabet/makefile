all: test

test: main.cpp alphabetPuzzle.cpp sdl_win_wrap.cpp texture.cpp
	g++ $^ -o test -g -I/usr/local/include -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm test

