all: test

test: main.o alphabetPuzzle.o sdl_win_wrap.o texture.o
	g++ $^ -g -gdwarf-2 -std=c++0x -static-libstdc++ -o alphabetPuzzle -I/usr/local/include -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf

%.o:%.cpp
	g++ -c $^ -I/usr/local/include -L/usr/local/lib
clean:
	rm test

