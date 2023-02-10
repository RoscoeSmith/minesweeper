#include "Menu.h"
#include "Board.h"
#include "Tile.h"
#include "termctrl.h"

// State machine states
enum State {
    INIT,
    EXIT,
    MENU_I,
    MENU,
    GAME
};

int main() {
    // Hold terminal environment data
    termios old_tio, new_tio;
    // Establish state machine
    int state = State::INIT;

    while (true) {
        switch (state) {
            case State::INIT: {
                // Init RNG
                srand(time(NULL));
                // Configure terminal environment [ChatGPT]
                tcgetattr(STDIN_FILENO, &old_tio);
                new_tio = old_tio;
                new_tio.c_lflag &= (~ICANON & ~ECHO);
                tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
                std::cout << "\e[?25l"; // hide cursor
                cls();
                state = State::MENU;
                break;
            }
            case State::EXIT: {
                // Reset terminal environment
                std::cout << "\e[?25h"; // show cursor
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                cls();
                return 0;
            }
            case State::MENU: {
                auto wsize = get_window_size();
                Menu menu(State::MENU, wsize.ws_col, wsize.ws_row, 1, 1);
                menu.add_button("Dummy", State::MENU);
                menu.add_int("Integer", 0, 10, 5, State::MENU);
                menu.add_button("Quit", State::EXIT);
                menu.set_title("Minesweeper TUI");
                menu.draw_title();
                menu.draw_item(0);
                menu.draw_item(1);
                menu.draw_item(2);
                while (true) {
                    state = menu.parse_input(get_input());
                    if (state != State::MENU) {
                        break;
                    }
                }
            }
        }
    }



    // Board b(10, 10, 10);
    // b.claim(5, 5);
    // b.setup_board();
    // cls();
    // print(b.get_string());
    // getchar();

    // while (true) {
    //     print("\n");
    //     int inp = get_input();
    //     print(std::to_string(inp));
    //     if (inp == Input::QUIT) { // ESC ESC
    //         break;
    //     }
    // }

    cls();
    return 0;
}