#include "Board.h"
#include "Tile.h"

Board::Board(int r, int c, int m) : row(r), col(c), mines(m) {
    tiles = row * col;
    flags = 0;
    std::priority_queue<int> minepos;
    std::set<int> minetrack;
    for (int i = 0; i < mines; ++i) {
        int pos = rand() % tiles;
        if (minetrack.find(pos) != minetrack.end()) {
            --i;
        } else {
            minetrack.insert(pos);
            minepos.push(pos);
        }
    }
}

int Board::get_col_count() {
    return col;
}

int Board::get_row_count() {
    return row;
}

Tile* Board::get_tile(int r, int c) {
    return grid[(c * col) + row];
}