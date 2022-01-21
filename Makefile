default : game

CC=g++
CCFLAGS=-lncurses -g
OFLAGS= $(CCFLAGS) -MMD
SRC = game.cpp fight.cpp inventory.cpp map.cpp player.cpp pokemon.cpp pokedex.cpp ui.cpp

#game : pokemon.o map.o player.o fight.o game.o pokedex.o
game : $(SRC:%.cpp=%.o)
	$(CC) $(CCFLAGS) $^ -o $@

game.o : game.cpp
	$(CC) $(OFLAGS) -c $<

%.o : %.cpp %.h
	$(CC) $(OFLAGS) -c $<

clean :
	rm *.o
	rm *.d

-include $(SRC:%.cpp=%.d)