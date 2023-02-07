#include "termctrl.h"
#include "Board.h"
#include "Tile.h"
#include <vector>
#include <algorithm>
#include <iomanip>

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
    std::vector<int> storage_int;
    std::vector<std::string> storage_str;

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
                state = State::MENU_I;
                break;
            }
            case State::EXIT: {
                // Reset terminal environment
                std::cout << "\e[?25h"; // show cursor
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                cls();
                return 0;
            }
            case State::MENU_I: {
                cls();
                print_at(2, 3,  "  Minesweeper TUI");
                print_at(5, 3,  "  Columns: <  9 >");
                print_at(7, 3,  "     Rows: < 10 >");
                print_at(9, 3,  "    Mines: < 10 >");
                print_at(11, 3, "      START      ");
                storage_int = {0, 9, 10, 10, 32, 32, 1023};
                storage_str = {"  Columns: ", "     Rows: ", "    Mines: ", "      START"};
                state = State::MENU;
            }
            case State::MENU: {
                // Storage Positions
                // 0: Menu position [0:3]
                // 1: Column amount [1:32]
                // 2: Row amount [1:32]
                // 3: Mine amount [1:1023]
                // 4: Max columns
                // 5: Max rows
                // 6: Max mines
                int action = get_input();
                switch (action) {
                    case Input::QUIT: // ESC ESC
                        state = State::EXIT;
                        break;
                    case Input::UP: { // Up
                        storage_int[0] == std::max(storage_int[0] - 1, 0);
                        break;
                    }
                    case Input::DOWN: { // Down
                        storage_int[0] == std::min(storage_int[0] + 1, 3);
                        break;
                    }
                    case Input::RIGHT: {
                        storage_int[storage_int[0] + 1] = std::min(storage_int[storage_int[0] + 1], storage_int[storage_int[0] + 4]);
                        break;
                    }
                    case Input::LEFT: {
                        storage_int[storage_int[0] + 1] = std::max(storage_int[storage_int[0] + 1], 1);
                    }
                    default:
                        break;
                }
                switch (action) {
                    case Input::UP || Input::DOWN || Input::RIGHT || Input::LEFT: {
                        set_window_cursor(((2 + storage_int[0]) * 2) + 1, 3);
                        clear_line();
                        std::cout << storage_str[storage_int[0]] << "\e[7m< " << std::setw(2) << storage_int[1] << " >\e[0m]" << std::flush;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }



    // Board b(10, 10, 10);
    // b.claim(5, 5);
    // b.setup_board();
    // cls();
    // print(b.get_string());


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