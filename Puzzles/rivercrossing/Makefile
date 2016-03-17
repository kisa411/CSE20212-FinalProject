CC=		g++
FLAGS=		-o
TARGETS=	Rivercrossing

all: $(TARGETS)

Rivercrossing: main.o Rivercrossing.h
	$(CC) $(FLAGS) $@ $^

main.o: main.cpp
	$(CC) -c $^

clean:
	rm *.o $(TARGETS)
