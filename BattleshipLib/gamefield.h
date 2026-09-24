#pragma once
#include "position.h"
#include "ship.h"
#include <vector>
#include <string>

// Состояние клетки поля
enum CellState {
    EMPTY,      // вода
    SHIP,       // корабль
    MISS,       // промах
    HIT,        // попадание
    SUNK        // потопленный корабль
};

// Класс GameField представляет игровое поле 10x10
class GameField {
private:
    const int SIZE = 10;
    std::vector<std::vector<CellState>> field;
    std::vector<Ship> ships;
    int shipsAlive;

public:
    GameField();

    bool placeShip(const Ship& ship);

    bool shoot(const Position& pos);

    CellState getCellState(const Position& pos) const;

    bool allShipsSunk() const;

    int getShipsAlive() const;

    void clear();

    void print(bool showShips = false) const;

    std::vector<std::vector<CellState>> getfield();
};

