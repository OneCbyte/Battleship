#include "game.h"
#include <iostream>

Game::Game(const std::string& name1, const std::string& name2)
    : player1(name1), player2(name2), currentPlayer(&player1), gameOver(false) {}

void Game::setupShips() {
    // GAYmer 1
    player1.placeShip(Ship(5, Position(0, 0), true));   
    player1.placeShip(Ship(4, Position(2, 0), true));   
    player1.placeShip(Ship(3, Position(4, 0), true));  
    player1.placeShip(Ship(3, Position(5, 0), true));   
    player1.placeShip(Ship(2, Position(7, 0), true));   
    player1.placeShip(Ship(2, Position(8, 0), true));   

    // GAYmer 2
    player2.placeShip(Ship(5, Position(0, 5), true));
    player2.placeShip(Ship(4, Position(2, 5), true));
    player2.placeShip(Ship(3, Position(4, 5), true));
    player2.placeShip(Ship(3, Position(5, 5), true));
    player2.placeShip(Ship(2, Position(7, 5), true));
    player2.placeShip(Ship(2, Position(8, 5), true));
}

bool Game::makeMove(const Position& pos) {
    if (gameOver) {
        return false;
    }

    Player& shooter = *currentPlayer;
    Player& defender = (currentPlayer == &player1) ? player2 : player1;

    bool hit = shooter.shootAt(defender.getField(), pos);

    // Проверка win$$$
    if (defender.getField().allShipsSunk()) {
        gameOver = true;
    }

    return hit;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

Player& Game::getCurrentPlayer() {
    return *currentPlayer;
}

const Player& Game::getCurrentPlayer() const {
    return *currentPlayer;
}

Player& Game::getOtherPlayer() {
    return (currentPlayer == &player1) ? player2 : player1;
}

const Player& Game::getOtherPlayer() const {
    return (currentPlayer == &player1) ? player2 : player1;
}

bool Game::isGameOver() const {
    return gameOver;
}

Player* Game::getWinner() {  
    if (!gameOver) {
        return nullptr;
    }
    return (player1.getField().allShipsSunk()) ? &player2 : &player1;
}


void Game::printStatus() const {
    std::cout << "\n=== Ход игрока: " << currentPlayer->getName() << " ===" << std::endl;
    std::cout << "Статистика: выстрелов=" << currentPlayer->getShotsFired()
        << ", попаданий=" << currentPlayer->getHitsMade()
        << ", точность=" << currentPlayer->getAccuracy() << "%" << std::endl;
}