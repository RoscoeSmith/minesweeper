#include <ncurses.h>
#include <iostream>

#include "Board.h"
#include "Tile.h"

int main() {
	srand(time(NULL));	// init rng

	// initscr();			/* Start curses mode 		  */
	// printw("Hello World !!!");	/* Print Hello World		  */
	// refresh();			/* Print it on to the real screen */
	// getch();			/* Wait for user input */
	// endwin();			/* End curses mode		  */

	Board b(10, 10, 10);
	b.claim(5, 5);
	b.setup_board();
	std::cout << b.get_string() << std::endl;

	return 0;
}