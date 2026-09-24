#include "gamefield.h"
#include <iostream>

GameField::GameField() : shipsAlive(0) {
    field.resize(SIZE, std::vector<CellState>(SIZE, EMPTY));
}

bool GameField::placeShip(const Ship& ship) {
    std::vector<Position> positions = ship.getPositions();

    for (const Position& pos : positions) {
        if (!pos.isValid()) {
            return false;
        }
    }

    for (const Position& pos : positions) {
        if (field[pos.getRow()][pos.getCol()] != EMPTY) {
            return false;
        }
    }

    for (const Position& pos : positions) {
        field[pos.getRow()][pos.getCol()] = SHIP;
    }

    ships.push_back(ship);
    shipsAlive++;
    return true;
}

bool GameField::shoot(const Position& pos) {
    if (!pos.isValid()) {
        return false;
    }

    CellState& cell = field[pos.getRow()][pos.getCol()];

    // Уже стреляли сюда
    if (cell == MISS || cell == HIT || cell == SUNK) {
        return false;
    }

    if (cell == SHIP) {
        // Попадание
        cell = HIT;

        // Проверка, потоплен ли корабль
        for (Ship& ship : ships) {
            if (ship.occupiesPosition(pos)) {
                ship.takeHit(pos);
                if (ship.isSunk()) {
                    // Пометить все клетки корабля как потопленные
                    for (const Position& p : ship.getPositions()) {
                        field[p.getRow()][p.getCol()] = SUNK;
                    }
                    shipsAlive--;  // ← ДОБАВИТЬ ЭТУ СТРОКУ
                }
                break;
            }
        }
        return true;
    }
    else {
        // Промах
        cell = MISS;
        return false;
    }
}

CellState GameField::getCellState(const Position& pos) const {
    if (!pos.isValid()) {
        return EMPTY;
    }
    return field[pos.getRow()][pos.getCol()];
}

bool GameField::allShipsSunk() const {
    return shipsAlive == 0;
}

int GameField::getShipsAlive() const {
    return shipsAlive;
}

void GameField::clear() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            field[i][j] = EMPTY;
        }
    }
    ships.clear();
    shipsAlive = 0;
}

void GameField::print(bool showShips) const {
    std::cout << "  ";
    for (int j = 0; j < SIZE; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < SIZE; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            char c = '.';
            switch (field[i][j]) {
            case EMPTY: c = '.'; break;
            case SHIP: c = showShips ? 'S' : '.'; break;
            case MISS: c = 'O'; break;
            case HIT: c = 'X'; break;
            case SUNK: c = '#'; break;
            }
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}