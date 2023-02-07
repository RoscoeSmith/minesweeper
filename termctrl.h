#pragma once

#include <iostream>
#include <utility>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Maps each possible input to an int
enum Input {
    UNKNOWN,
    QUIT,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    CONFIRM,
    DENY,
    M1,
    M2,
    M3
};

void set_window_cursor(int r, int c) {
    std::cout << "\e[" << std::to_string(r) << ";" << std::to_string(c) << "H" << std::flush;
}

void store_cursor() {
    std::cout << "\e[s";
}

void restore_cursor() {
    std::cout << "\e[u";
}

std::pair<int, int> get_cursor_pos() {
    std::cout << "\e[6n";
    std::cout.flush();
    char ch;
    std::string response = "";
    while (true) {
        ch = getchar();
        response.push_back(ch);
        if (ch == 'R') {
            break;
        }
    }
    int row, col;
    sscanf(response.c_str(), "\e[%d;%dR", &row, &col);
    return std::make_pair(row, col);
}

// Print the given string to the screen at the terminal cursor
void print(std::string str) {
    std::cout << str  << std::flush;
}

void print_at(int r, int c, std::string str) {
    set_window_cursor(r, c);
    print(str);
}

void print_at_r(int r, int c, std::string str) {
    store_cursor();
    print_at(r, c, str);
    restore_cursor();
}

void clear_from_cursor() {
    std::cout << "\e[J" << std::flush;
}

// Clear the screen and set terminal cursor to 1;1
void cls() {
    std::cout << "\e[2J\e[1;1H";
    std::cout.flush();
}

struct winsize get_window_size() {
    struct winsize wsize;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize);
    return wsize;
}

int get_window_rows() {
    return (int) get_window_size().ws_row;
}

int get_input() {
    int ch = getchar();
    switch (ch) {
        case 27: {
            print_at_r(get_window_rows(), 1, "\e[7mESC\e[0m");
            int ch2 = getchar();
            if (ch2 == 27) {
                std::cout << "double escape" << std::endl;
            } else if (ch2 == 91) {
                std::cout << "arrow: " << getchar() << std::endl;
            }
            clear_from_cursor();
            break;
        } default:
            break;
    }
    return ch;
}