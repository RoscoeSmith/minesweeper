#include "termctrl.h"
#include "Board.h"
#include "Tile.h"

int main() {
    // Init RNG
    srand(time(NULL));
    // Configure terminal environment [ChatGPT]
    termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    std::cout << "\e[?25l";

    auto cursor = get_cursor_pos();
    std::cout << cursor.first << " " << cursor.second << std::endl;

    // Board b(10, 10, 10);
    // b.claim(5, 5);
    // b.setup_board();
    // cls();
    // print(b.get_string());
    while (true) {
        print("\n");
        int ch = get_input();
        print(std::to_string(ch));
        if (ch == 97) { // 'a'
            break;
        }
    }
    cls();

    // Reset terminal environment
    std::cout << "\e[?25h";
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return 0;
}