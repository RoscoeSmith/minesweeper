#pragma once

#include <string>
#include <vector>
#include <queue>
#include <set>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <iostream>

class Tile;

class Board {
public:
    Board(int r, int c, int m);
    // getters
    int get_row_count();
    int get_col_count();
    std::shared_ptr<Tile> get_tile(int r, int c);
    std::shared_ptr<Tile> get_tile(int idx);
    // setters
    void setup_board();
    void claim(int r, int c);
    void open_claimed();
    // io
    std::string get_string();
    // operations
    bool open(int r, int c);
    void end_game();

private:
    int row;
    int col;
    int tiles;
    int mines;
    int flags;
    std::vector<std::shared_ptr<Tile>> grid;
    std::vector<std::shared_ptr<Tile>> holding;
};