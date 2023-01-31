#include "Board.h"
#include "Tile.h"

Board::Board(int r, int c, int m) : row(r), col(c), mines(m) {
    tiles = row * col;
    flags = 0;
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            auto ptr = std::make_shared<Tile>(y, x, 0, this);
            grid.push_back(ptr);
        }
    }
}

int Board::get_col_count() {
    return col;
}

int Board::get_row_count() {
    return row;
}

std::shared_ptr<Tile> Board::get_tile(int r, int c) {
    return grid[(r * row) + c];
}

std::shared_ptr<Tile> Board::get_tile(int idx) {
    return grid[idx];
}

// setters

void Board::setup_board() {
    std::priority_queue<int> minepos;
    std::set<int> minetrack;
    while (minetrack.size() < mines) {
        int pos = rand() % tiles;
        // tile chosen was already opened
        if (get_tile(pos)->is_open()) {
            continue;
        }
        // tile was already chosen before
        if (minetrack.find(pos) != minetrack.end()) {
            continue;
        }
        minetrack.insert(pos);
        minepos.push(pos);
    }
    while (minepos.size() != 0) {
        int pos = minepos.top();
        get_tile(pos)->init_set_bomb();
        minepos.pop();
    }
}

// io

std::string Board::get_string() {
    std::string out = "";
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            out += get_tile(y, x)->get_string();
        }
        out += "\n";
    }
    return out;
}