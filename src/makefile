
SRC_DIR = ../src
INC_DIR = ../inc

CXX = gcc
CC = $(CXX)

WARNINGS = -ansi -pedantic -g 
CXXFLAGS = $(WARNINGS) 

CPPFLAGS = -I$(INC_DIR)

TARGET = run
OBJS = ./cards.o ./deck.o ./game.o ./main.o ./players.o ./rounds.o ./vector.o ./ui.o ./sorting_algorithms.o ./strategy.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)


./cards.o:  $(INC_DIR)/cards.h 
./deck.o: $(INC_DIR)/deck.h $(INC_DIR)/vector.h $(INC_DIR)/cards.h $(INC_DIR)/enum.h
./game.o: $(INC_DIR)/game.h $(INC_DIR)/rounds.h $(INC_DIR)/players.h $(INC_DIR)/ui.h $(INC_DIR)/enum.h
./main.o:  $(INC_DIR)/game.h
./players.o: $(INC_DIR)/players.h $(INC_DIR)/vector.h $(INC_DIR)/cards.h $(INC_DIR)/enum.h $(INC_DIR)/sorting_algorithms.h
./rounds.o:  $(INC_DIR)/rounds.h $(INC_DIR)/vector.h $(INC_DIR)/players.h $(INC_DIR)/deck.h $(INC_DIR)/enum.h $(INC_DIR)/ui.h 
./vector.o:  $(INC_DIR)/vector.h $(INC_DIR)/deck.h	
./ui.o:  $(INC_DIR)/ui.h $(INC_DIR)/cards.h $(INC_DIR)/vector.h $(INC_DIR)/players.h
strategy.o: $(INC_DIR)/strategy.h $(INC_DIR)/players.h

check: $(TARGET)
	./$(TARGET) 

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean
