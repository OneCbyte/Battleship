#pragma once

#include "gamefield.h"
#include <string>

// Класс Player представляет игрока
class Player {
private:
    std::string name;
    GameField field;
    int shotsFired;
    int hitsMade;

public:
    Player();
    Player(const std::string& n);

    std::string getName() const;
    GameField& getField();
    const GameField& getField() const;
    int getShotsFired() const;
    int getHitsMade() const;

    bool shootAt(GameField& enemyField, const Position& pos);

    bool placeShip(const Ship& ship);

    double getAccuracy() const;
};
