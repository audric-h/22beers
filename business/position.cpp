#include "position.h"
#include "board.h"
#include <iostream>

namespace quoridor {

Position::Position(unsigned row, unsigned column) {
    if(row > Board::getSize()-1 || column > Board::getSize()-1) {
        throw std::invalid_argument { "Position non valide" };
    }
    row_ = row;
    column_ = column;
}

unsigned Position::getRow() const {
    return row_;
}

unsigned Position::getColumn() const {
    return column_;
}

bool Position::move(int row, int column) {
    try {
        Position p(row_+row,column_+column);
    } catch (std::invalid_argument e) {
        return false;
    }
    row_ += row;
    column_ += column;
    return true;
}

}
