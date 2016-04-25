all: test

test: main.cpp hangman.cpp sdl_win_wrap.cpp texture.cpp
	g++ $^ -o hangman -g -gdwarf-2 -std=c++0x -static-libstdc++ -lSDL2_image -lSDL2_ttf 

clean:
	rm test
