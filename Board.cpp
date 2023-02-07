#include "Board.h"
#include "Tile.h"

Board::Board(int r, int c, int m) : row(r), col(c), mines(m) {
    c_r = 0;
    c_c = 0;
    tiles = row * col;
    flags = 0;
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            auto ptr = std::make_shared<Tile>(y, x, 0, this);
            grid.push_back(ptr);
        }
    }
}

// getters

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

std::shared_ptr<Tile> Board::get_cursor_tile() {
    return get_tile(c_r, c_c);
}

// setters

void Board::setup_board() {
    std::priority_queue<int> minepos;
    std::set<int> minetrack;
    while (minetrack.size() < (long unsigned int) mines) {
        int pos = rand() % tiles;
        // tile chosen was already opened
        if (get_tile(pos)->is_open() || get_tile(pos)->is_claimed()) {
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
    open_claimed();
}

void Board::claim(int r, int c) {
    auto tile = get_tile(r, c);
    tile->claim();
    holding.push_back(tile);
}

void Board::open_claimed() {
    std::cout << holding.size() << std::endl;
    for (auto tile : holding) {
        tile->open();
    }
    holding.clear();
}

void Board::set_cursor(int r, int c) {
    if (r >= 0 && r < get_row_count()) {
        c_r = r;
    }
    if (c >= 0 && c < get_col_count()) {
        c_c = c;
    }
}
void Board::move_cursor(int r, int c) {
    // set row
    if (r < 0) {
        c_r = std::max(c_r + r, 0);
    } else if (r > 0) {
        c_r = std::min(c_r + r, get_row_count() - 1);
    }
    // set column
    if (c < 0) {
        c_c = std::max(c_c + c, 0);
    } else if (c > 0) {
        c_c = std::min(c_c + c, get_col_count() - 1);
    }
}

// io

std::string Board::get_string() {
    std::string out = "";
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            auto tile = get_tile(y, x);
            if (tile == get_cursor_tile()) {
                out += tile->get_string(true);
            } else {
                out += tile->get_string();
            }
        }
        out += "\n";
    }
    return out;
}

// operations

bool Board::open(int r, int c) {
    int result = get_tile(r, c)->open();
    if (result == -1) {
        return false;
    }
    return true;
}

void Board::end_game() {
    return;
}