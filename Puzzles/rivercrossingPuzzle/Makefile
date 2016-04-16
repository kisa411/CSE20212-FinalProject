CC=		g++
FLAGS=		-g -gdwarf-2 -lSDL2_image -lSDL2_ttf -o
TARGETS=	Rivercrossing

all: $(TARGETS)

Rivercrossing: main.cpp Rivercrossing.cpp sdl_win_wrap.cpp texture.cpp 
	$(CC) $(FLAGS) $@ $^

clean:
	rm $(TARGETS)
