#include "Tile.h"
#include "Board.h"

Tile::Tile(int r, int c, int n, Board* b) : row(r), col(c), number(n), board(b) {
    flag = false;
    opened = false;
}

// getters

bool Tile::is_open() {
    return opened;
}

bool Tile::has_flag() {
    return flag;
}

std::vector<Tile*> Tile::get_neighbors() {
    std::vector<Tile*> neighbors;
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
        if (n->has_flag()) {
            ++flags;
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
}

void Tile::open_neighbors() {
    auto neighbors = get_neighbors();
    for (auto n : neighbors) {
        if (n->open() == 0) {
            n->open_neighbors();
        }
    }
}

bool Tile::toggle_flag() {
    flag = ~flag;
}