#include <iostream>
#include <limits>
#include "game.h"

Position getInputPosition(const std::string& playerName) {
    int row, col;

    while (true) {
        std::cout << "\n" << playerName << ", введите координаты выстрела (строка столбец, 0-9): ";
        std::cin >> row >> col;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите два числа!" << std::endl;
            continue;
        }

        Position pos(row, col);
        if (!pos.isValid()) {
            std::cout << "Ошибка: координаты должны быть от 0 до 9!" << std::endl;
            continue;
        }

        return pos;
    }
}

void clearScreen() {
    system("clear");
}

int main() {
    setlocale(LC_ALL, "rus");
    std::cout << "=== МОРСКОЙ БОЙ ===" << std::endl;
    std::cout << "Игра для двух игроков на одном устройстве\n" << std::endl;

    std::string name1, name2;
    std::cout << "Игрок 1, введите ваше имя: ";
    std::getline(std::cin >> std::ws, name1);
    std::cout << "Игрок 2, введите ваше имя: ";
    std::getline(std::cin >> std::ws, name2);

    Game game(name1, name2);
    game.setupShips();

    std::cout << "\nКорабли расставлены. Начинаем игру!\n" << std::endl;

    int turn = 1;
    while (!game.isGameOver()) {
        Player& current = game.getCurrentPlayer();
        Player& other = game.getOtherPlayer();

        std::cout << "\n=== ХОД " << turn << " ===" << std::endl;
        std::cout << "Сейчас ходит: " << current.getName() << std::endl;

        std::cout << "Ваша статистика: выстрелов=" << current.getShotsFired()
            << ", попаданий=" << current.getHitsMade()
            << ", точность=" << current.getAccuracy() << "%" << std::endl;

        Position shot = getInputPosition(current.getName());

        bool hit = game.makeMove(shot);

        if (hit) {
            std::cout << ">>> ПОПАДАНИЕ! Стреляйте снова! <<<" << std::endl;
        }
        else {
            std::cout << ">>> ПРОМАХ. Ход переходит к " << other.getName() << " <<<" << std::endl;
            game.switchPlayer();
            turn++;
        }

        if (!game.isGameOver()) {
            std::cout << "\nНажмите Enter для продолжения..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            clearScreen();
        }
    }

    std::cout << "\n=== ИГРА ОКОНЧЕНА ===" << std::endl;
    Player* winner = game.getWinner();
    std::cout << "ПОБЕДИТЕЛЬ: " << winner->getName() << "!" << std::endl;
    std::cout << "Итоговая статистика:" << std::endl;
    std::cout << winner->getName() << ": выстрелов=" << winner->getShotsFired()
        << ", попаданий=" << winner->getHitsMade()
        << ", точность=" << winner->getAccuracy() << "%" << std::endl;

    return 0;
}

