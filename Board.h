#pragma once

#include <vector>
#include <queue>
#include <set>
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
    Tile* get_tile(int r, int c);

private:
    int row;
    int col;
    int tiles;
    int mines;
    int flags;
    std::vector<Tile*> grid;
};