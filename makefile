OBJS	= minesweeper.o Tile.o Board.o Menu.o termctrl.o
SOURCE	= minesweeper.cpp Tile.cpp Board.cpp Menu.cpp termctrl.cpp
HEADER	= Tile.h Board.h Menu.h termctrl.h
OUT	= minesweeper
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 
VER		 = c++2a

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

minesweeper.o: minesweeper.cpp
	$(CC) $(FLAGS) minesweeper.cpp -std=$(VER)

Tile.o: Tile.cpp
	$(CC) $(FLAGS) Tile.cpp -std=$(VER)

Board.o: Board.cpp
	$(CC) $(FLAGS) Board.cpp -std=$(VER)

Menu.o: Menu.cpp
	$(CC) $(FLAGS) Menu.cpp -std=$(VER)

termctrl.o: termctrl.cpp
	$(CC) $(FLAGS) termctrl.cpp -std=$(VER)


clean:
	rm -f $(OBJS) $(OUT)