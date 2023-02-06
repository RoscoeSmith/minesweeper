#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Board;

const std::unordered_map<int, const char *> tilemap = {
    {-1, "＊"},
    {0, "　"},
    {1, "１"},
    {2, "２"},
    {3, "３"},
    {4, "４"},
    {5, "５"},
    {6, "６"},
    {7, "７"},
    {8, "８"},
    {9, "９"}
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
    std::string get_string();
private:
    int row;
    int col;
    int number;
    bool flag;
    bool opened;
    bool claimed;
    Board* board;
};