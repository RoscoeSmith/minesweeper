#include "Menu.h"
#include "Board.h"
#include "Tile.h"
#include "termctrl.h"

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
                Menu menu(80, 24, 1, 1);
                menu.add_button("Button");
                menu.add_button("Button 2");
                menu.draw_item(0);
                menu.draw_item(1);
                getchar();
                state = State::EXIT;
            }
            case State::MENU: {
                break;
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