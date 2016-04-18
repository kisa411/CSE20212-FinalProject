CC=		g++
FLAGS=		-g -gdwarf-2 -lSDL2_image -lSDL2_ttf -static-libstdc++ -std=c++11 -I/usr/local/include -L/usr/local/lib -o
TARGETS=	Rivercrossing

all: $(TARGETS)

Rivercrossing: main.cpp Rivercrossing.cpp sdl_win_wrap.cpp texture.cpp 
	$(CC) $(FLAGS) $@ $^

clean:
	rm $(TARGETS)
