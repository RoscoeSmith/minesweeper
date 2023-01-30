OBJS	= minesweeper.o Tile.o Board.o
SOURCE	= minesweeper.cpp Tile.cpp Board.cpp
HEADER	= Tile.h Board.h
OUT	= minesweeper
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses
VER		 = c++2a

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

minesweeper.o: minesweeper.cpp
	$(CC) $(FLAGS) minesweeper.cpp -std=$(VER)

Tile.o: Tile.cpp
	$(CC) $(FLAGS) Tile.cpp -std=$(VER)

Board.o: Board.cpp
	$(CC) $(FLAGS) Board.cpp -std=c++17


clean:
	rm -f $(OBJS) $(OUT)