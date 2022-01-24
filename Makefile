default : game

CC=g++
CCFLAGS=-lncurses -g -Wall
OFLAGS= $(CCFLAGS) -MMD
SRC = game.cpp fight.cpp inventory.cpp map.cpp player.cpp pokemon.cpp pokedex.cpp ui.cpp

#game : pokemon.o map.o player.o fight.o game.o pokedex.o
game : $(SRC:%.cpp=%.o)
	$(CC) $^ -o $@ $(CCFLAGS)

game.o : game.cpp
	$(CC) -c $< $(OFLAGS)

%.o : %.cpp %.h
	$(CC) -c $< $(OFLAGS)

clean :
	rm *.o
	rm *.d

-include $(SRC:%.cpp=%.d)
