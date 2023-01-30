#include "Board.h"

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