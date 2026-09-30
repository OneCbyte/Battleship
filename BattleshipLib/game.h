#pragma once

#include "player.h"

// Класс Game управляет игровым процессом
class Game {
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    bool gameOver;

public:
    Game(const std::string& name1, const std::string& name2);

    void setupShips();

    bool makeMove(const Position& pos);

    void switchPlayer();

    Player& getCurrentPlayer();
    const Player& getCurrentPlayer() const;

    Player& getOtherPlayer();
    const Player& getOtherPlayer() const;

    bool isGameOver() const;

    Player* getWinner();

    void printStatus() const;
};
