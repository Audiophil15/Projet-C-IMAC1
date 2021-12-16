all : game

CC=g++
CCFLAGS=-lncurses

game : pokemon.o map.o player.o game.o
	$(CC) $(CCFLAGS) $^ -o $@

game.o : game.cpp
	$(CC) $(CCFLAGS) -c $<

pokemon.o : pokemon.cpp pokemon.h
	$(CC) $(CCFLAGS) -c $<

map.o : map.cpp map.h
	$(CC) $(CCFLAGS) -c $<

player.o : player.cpp player.h
	$(CC) $(CCFLAGS) -c $<

clean :
	rm *.o