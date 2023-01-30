#include <ncurses.h>
#include "Board.h"

int main() {
	srand(time(NULL));	// init rng

	// initscr();			/* Start curses mode 		  */
	// printw("Hello World !!!");	/* Print Hello World		  */
	// refresh();			/* Print it on to the real screen */
	// getch();			/* Wait for user input */
	// endwin();			/* End curses mode		  */

	Board b(10, 10, 10);

	return 0;
}