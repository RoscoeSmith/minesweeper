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

	std::string out = "";
    for (int y = 0; y < b.get_row_count(); ++y) {
        for (int x = 0; x < b.get_col_count(); ++x) {
            auto tile = b.grid[(x * b.get_col_count()) + y];
            out += tile->is_open();
        }
        out += "\n";
    }
	std::cout << out << std::endl;

	// std::cout << b.get_string() << std::endl;
	// b.setup_board();
	std::cout << "lol" << std::endl;

	return 0;
}