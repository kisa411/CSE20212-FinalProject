all: test

test: main.cpp singaporePuzzle.cpp sdl_win_wrap.cpp texture.cpp
	g++ $^ -o singapore -g -gdwarf-2 -std=c++0x -I/usr/local/include -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf -static-libstdc++

clean:
	rm test
