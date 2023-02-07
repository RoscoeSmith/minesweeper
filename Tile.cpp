#include "Tile.h"
#include "Board.h"

Tile::Tile(int r, int c, int n, Board* b) : row(r), col(c), number(n), board(b) {
    flag = false;
    opened = false;
    claimed = false;
}

// getters

bool Tile::is_open() {
    return opened;
}

bool Tile::has_flag() {
    return flag;
}

bool Tile::is_claimed() {
    return claimed;
}

std::vector<std::shared_ptr<Tile>> Tile::get_neighbors() {
    std::vector<std::shared_ptr<Tile>> neighbors;
    for (int r = -1; r < 2; ++r) {
        if (row + r < 0 || row + r >= board->get_row_count()) {
            neighbors.push_back(nullptr);
            continue;
        }
        for (int c = -1; c < 2; ++c) {
            if (col + c < 0 || col + c >= board->get_col_count()) {
                neighbors.push_back(nullptr);
                continue;
            }
            neighbors.push_back(board->get_tile(row + r, col + c));
        }
    }
    return neighbors;
}

// setters

int Tile::open() {
    if (is_open()) {
        return -2; // tile was already opened
    } else {
        opened = true;
        if (number == 0) {
            auto neighbors = get_neighbors();
            for (auto neighbor : neighbors) {
                if (neighbor != nullptr) {
                    neighbor->open();
                }
            }
        }
        return number;
    }
}

bool Tile::area_scan() {
    if (!is_open()) {
        return true; // tile isn't open yet
    }
    auto neighbors = get_neighbors(); // get neighbors of tile
    // check if there are sufficient flags
    int flags = 0;
    for (auto n : neighbors) {
        if (n != nullptr) {
            if (n->has_flag()) {
                ++flags;
            }
        }
    }
    if (flags < number) {
        return true; // not enough flags on neighbors
    }
    for (auto n : neighbors) {
        int num = n->open();
        if (num == -1) {
            return false; // neighbor was a misflagged bomb
        } else if (num == 0) {
            n->open_neighbors();
        }
    }
    return true;
}

void Tile::open_neighbors() {
    auto neighbors = get_neighbors();
    for (auto n : neighbors) {
        if (n != nullptr) {
            if (n->open() == 0) {
                n->open_neighbors();
            }
        }
    }
}

bool Tile::toggle_flag() {
    flag = !flag;
    return flag;
}

void Tile::init_set_bomb() {
    number = -1;
    auto neighbors = get_neighbors();
    for (auto neighbor : neighbors) {
        if (neighbor != nullptr) {
            neighbor->init_inc_number();
        }
    }
}

void Tile::init_inc_number() {
    if (number != -1) {
        number += 1;
    }
}

void Tile::claim() {
    claimed = true;
}

//io

std::string Tile::get_string(bool is_cursor) {
    const std::unordered_map<int, const char *>* mapper;
    if (is_cursor) {
        mapper = &tilemap_highlight;
    } else {
        mapper = &tilemap;
    }
    std::string out = "";
    if (!is_open()) {
        if (!has_flag()) {
            out += mapper->at(-2);
        } else {
            out += mapper->at(-3);
        }
    } else {
        out += mapper->at(number);
    }
    return out;    
}