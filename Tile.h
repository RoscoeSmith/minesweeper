#pragma once

#include <vector>

class Board;

class Tile {
public:
    Tile(int r, int c, int n, Board* b);
    // getters
    bool is_open();
    bool has_flag();
    std::vector<Tile*> get_neighbors();
    // setters
    int open();
    bool area_scan();
    void open_neighbors();
    bool toggle_flag();
private:
    int row;
    int col;
    int number;
    bool flag;
    bool opened;
    Board* board;
};