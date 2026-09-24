#include <iostream>
#include "game.h"

int main() {
    setlocale(LC_ALL, "rus");
    std::cout << "=== МОРСКОЙ БОЙ ===" << std::endl;

    Game game("Игрок 1", "Игрок 2");
    game.setupShips();

    int turn = 0;
    while (!game.isGameOver() && turn < 20) {
        game.printStatus();

        Position shot(turn % 10, turn % 10);
        bool hit = game.makeMove(shot);

        std::cout << "Выстрел в " << shot << " -> "
            << (hit ? "ПОПАДАНИЕ!" : "ПРОМАХ") << std::endl;

        game.switchPlayer();
        turn++;
    }

    if (game.isGameOver()) {
        Player* winner = game.getWinner();
        std::cout << "\n=== ПОБЕДИТЕЛЬ: " << winner->getName() << " ===" << std::endl;
    }
    else {
        std::cout << "\n=== Игра ещё не закончена ===" << std::endl;
    }

    return 0;
}

