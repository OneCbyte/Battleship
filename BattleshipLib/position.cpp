#include "position.h"

Position::Position() : row(0), col(0) {}

Position::Position(int r, int c) : row(r), col(c) {}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return col;
}

void Position::setRow(int r) {
    row = r;
}

void Position::setCol(int c) {
    col = c;
}

bool Position::isValid() const {
    return row >= 0 && row < 10 && col >= 0 && col < 10;
}

bool Position::operator==(const Position& other) const {
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.row << ", " << pos.col << ")";
    return os;
}