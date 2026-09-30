#pragma once

#include <iostream>

// Координата на игровом поле
class Position {
private:
    int row;   
    int col;  

public:
    Position();
    Position(int r, int c);

    int getRow() const;
    int getCol() const;

    void setRow(int r);
    void setCol(int c);


    bool isValid() const;


    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};