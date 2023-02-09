#ifndef TERMCTRL_H
#define TERMCTRL_H

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

void set_window_cursor(int r, int c);

void store_cursor();

void restore_cursor();

std::pair<int, int> get_cursor_pos();

// Print the given string to the screen at the terminal cursor
void print(std::string str);

void print_at(int r, int c, std::string str);

void print_at_r(int r, int c, std::string str);

void clear_from_cursor();

void clear_line();

// Clear the screen and set terminal cursor to 1;1
void cls();

struct winsize get_window_size();

int get_window_rows();

int get_input();

#endif