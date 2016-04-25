all: test

test: main.cpp opening.cpp sdl_win_wrap.cpp texture.cpp
	g++ $^ -o alphabet -g -gdwarf-2 -static-libstdc++ -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++0x
	
clean:
	rm opening

