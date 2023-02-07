#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Board;

const std::unordered_map<int, const char *> tilemap = {
    {-3, "\e[31;47mＰ\e[0m"}, // flag
    {-2, "\e[90;47m::\e[0m"}, // unopened
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

const std::unordered_map<int, const char *> tilemap_highlight = {
    {-3, "\e[31;106mＰ\e[0m"}, // flag
    {-2, "\e[90;106m::\e[0m"}, // unopened
    {-1, "\e[30;101m＊\e[0m"}, // bomb
    {0, "\e[106m　\e[0m"},
    {1, "\e[90;46m１\e[0m"},
    {2, "\e[90;46m２\e[0m"},
    {3, "\e[90;46m３\e[0m"},
    {4, "\e[90;46m４\e[0m"},
    {5, "\e[90;46m５\e[0m"},
    {6, "\e[90;46m６\e[0m"},
    {7, "\e[90;46m７\e[0m"},
    {8, "\e[90;46m８\e[0m"}
};

class Tile {
public:
    Tile(int r, int c, int n, Board* b);
    // getters
    bool is_open();
    bool has_flag();
    bool is_claimed();
    std::vector<std::shared_ptr<Tile>> get_neighbors();
    // setters
    int open();
    bool area_scan();
    void open_neighbors();
    bool toggle_flag();
    void init_set_bomb();
    void init_inc_number();
    void claim();
    // io
    std::string get_string(bool is_cursor = false);
private:
    int row;
    int col;
    int number;
    bool flag;
    bool opened;
    bool claimed;
    Board* board;
};