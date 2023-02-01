#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Board;

const std::unordered_map<int, const char *> tilemap = {
    {-1, "\e[30;41m＊\e[0m"},
    {0, "\e[100m　\e[0m"},
    {1, "\e[94;100m１\e[0m"},
    {2, "\e[32;100m２\e[0m"},
    {3, "\e[91;100m３\e[0m"},
    {4, "\e[34;100m４\e[0m"},
    {5, "\e[31;100m５\e[0m"},
    {6, "\e[36;100m６\e[0m"},
    {7, "\e[35;100m７\e[0m"},
    {8, "\e[37;100m８\e[0m"}
};

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