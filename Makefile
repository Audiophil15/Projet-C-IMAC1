all : game

CC=g++
CCFLAGS=-lncurses

game : pokemon.o board.o player.o game.o
	$(CC) $(CCFLAGS) $^ -o $@

game.o : game.cpp
	$(CC) $(CCFLAGS) -c $<

pokemon.o : pokemon.cpp pokemon.h
	$(CC) $(CCFLAGS) -c $<

board.o : board.cpp board.h
	$(CC) $(CCFLAGS) -c $<

player.o : player.cpp player.h
	$(CC) $(CCFLAGS) -c $<

clean :
	rm *.o