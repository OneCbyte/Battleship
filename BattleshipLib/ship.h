#pragma once

#include "position.h"
#include <vector>

// Типы кораблей по размеру
enum ShipType {
    DESTROYER = 2,  
    CRUISER = 3,     
    BATTLESHIP = 4,  
    CARRIER = 5    
};

// Класс Ship представляет корабль на поле
class Ship {
private:
    int size;                
    Position start;         
    bool isHorizontal;           
    std::vector<bool> hits;  
    bool sunk;                   

public:
    Ship();
    Ship(int s, const Position& pos, bool horizontal);

    int getSize() const;
    Position getStart() const;
    bool getIsHorizontal() const;
    bool isSunk() const;

    void setStart(const Position& pos);
    void setIsHorizontal(bool h);

    std::vector<Position> getPositions() const;

    bool isHit(const Position& pos) const;

    void takeHit(const Position& pos);

    bool occupiesPosition(const Position& pos) const;
};