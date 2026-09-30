#include "ship.h"

Ship::Ship() : size(2), start(0, 0), isHorizontal(true), sunk(false) {
    hits.resize(size, false);
}

Ship::Ship(int s, const Position& pos, bool horizontal)
    : size(s), start(pos), isHorizontal(horizontal), sunk(false) {
    hits.resize(size, false);
}

int Ship::getSize() const {
    return size;
}

Position Ship::getStart() const {
    return start;
}

bool Ship::getIsHorizontal() const {
    return isHorizontal;
}

bool Ship::isSunk() const {
    return sunk;
}

void Ship::setStart(const Position& pos) {
    start = pos;
}

void Ship::setIsHorizontal(bool h) {
    isHorizontal = h;
}

std::vector<Position> Ship::getPositions() const {
    std::vector<Position> positions;
    for (int i = 0; i < size; ++i) {
        if (isHorizontal) {
            positions.push_back(Position(start.getRow(), start.getCol() + i));
        }
        else {
            positions.push_back(Position(start.getRow() + i, start.getCol()));
        }
    }
    return positions;
}

bool Ship::isHit(const Position& pos) const {
    std::vector<Position> positions = getPositions();
    for (size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] == pos && hits[i]) {
            return true;
        }
    }
    return false;
}

void Ship::takeHit(const Position& pos) {
    std::vector<Position> positions = getPositions();
    for (size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] == pos) {
            hits[i] = true;
            break;
        }
    }

    sunk = true;
    for (bool hit : hits) {
        if (!hit) {
            sunk = false;
            break;
        }
    }
}

bool Ship::occupiesPosition(const Position& pos) const {
    std::vector<Position> positions = getPositions();
    for (const Position& p : positions) {
        if (p == pos) {
            return true;
        }
    }
    return false;
}