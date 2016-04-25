CC=		g++
FLAGS=		-g -gdwarf-2 -lSDL2_image -lSDL2_ttf -static-libstdc++ -std=gnu++11 -std=c++11 -o
TARGETS=	Blackjack

all: $(TARGETS)

Blackjack: main.cpp Blackjack.cpp CardDeck.cpp sdl_win_wrap.cpp texture.cpp 
	$(CC) $(FLAGS) $@ $^

clean:
	rm $(TARGETS)
