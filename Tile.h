#pragma once

#include <string>
#include <vector>
#include <memory>

class Board;

class Tile {
public:
    Tile(int r, int c, int n, Board* b);
    // getters
    bool is_open();
    bool has_flag();
    std::vector<std::shared_ptr<Tile>> get_neighbors();
    // setters
    int open();
    bool area_scan();
    void open_neighbors();
    bool toggle_flag();
    void init_set_bomb();
    void init_inc_number();
    // io
    std::string get_string();
private:
    int row;
    int col;
    int number;
    bool flag;
    bool opened;
    Board* board;
};