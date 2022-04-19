
TARGET = ran
CC = gcc
CFLAGS = -ansi -pedantic -g
OBJS = cards.o deck.o game.o main.o players.o rounds.o vector.o userInterface.o SortingAlgorithms.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm
	
cards.o: cards.c cards.h 
	$(CC) $(CFLAGS) -c cards.c
	
deck.o: deck.c deck.h vector.h cards.h enum.h
	$(CC) $(CFLAGS) -c deck.c
	
game.o: game.c game.h rounds.h players.h userInterface.h enum.h
	$(CC) $(CFLAGS) -c game.c
	
main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c
	
players.o: players.c players.h vector.h cards.h enum.h SortingAlgorithms.h
	$(CC) $(CFLAGS) -c players.c
	
rounds.o: rounds.c rounds.h vector.h players.h deck.h enum.h userInterface.h 
	$(CC) $(CFLAGS) -c rounds.c
	
vector.o: vector.c vector.h deck.h
	$(CC) $(CFLAGS) -c vector.c
	
userInterface.o: userInterface.c userInterface.h cards.h vector.h
	$(CC) $(CFLAGS) -c userInterface.c
		
clean:
	rm -f $(TARGET) $(OBJS)
