all: test

test: main.cpp cryptography.cpp texture.cpp sdl_win_wrap.cpp
	g++ $^ -g -gdwarf-2 -std=c++0x -static-libstdc++ -o test -lSDL2_image -lSDL2_ttf
