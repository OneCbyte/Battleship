#include "player.h"

Player::Player() : name("Player"), shotsFired(0), hitsMade(0) {}

Player::Player(const std::string& n) : name(n), shotsFired(0), hitsMade(0) {}

std::string Player::getName() const {
    return name;
}

GameField& Player::getField() {
    return field;
}

const GameField& Player::getField() const {
    return field;
}

int Player::getShotsFired() const {
    return shotsFired;
}

int Player::getHitsMade() const {
    return hitsMade;
}

bool Player::shootAt(GameField& enemyField, const Position& pos) {
    shotsFired++;
    bool hit = enemyField.shoot(pos);
    if (hit) {
        hitsMade++;
    }
    return hit;
}

bool Player::placeShip(const Ship& ship) {
    return field.placeShip(ship);
}

double Player::getAccuracy() const {
    if (shotsFired == 0) return 0.0;
    return (double)hitsMade / shotsFired * 100.0;
}