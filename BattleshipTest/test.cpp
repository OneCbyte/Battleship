#include "pch.h"
#include <gtest/gtest.h>
#include "position.h"
#include "ship.h"
#include "gameField.h"
#include "player.h"
#include "game.h"


TEST(PositionTest, DefaultConstructor) {
    Position pos;
    EXPECT_EQ(pos.getRow(), 0);
    EXPECT_EQ(pos.getCol(), 0);
}

TEST(PositionTest, ParameterizedConstructor) {
    Position pos(5, 7);
    EXPECT_EQ(pos.getRow(), 5);
    EXPECT_EQ(pos.getCol(), 7);
}

TEST(PositionTest, IsValid_Valid) {
    Position pos(3, 4);
    EXPECT_TRUE(pos.isValid());
}

TEST(PositionTest, IsValid_Invalid_Row) {
    Position pos(-1, 5);
    EXPECT_FALSE(pos.isValid());
}

TEST(PositionTest, IsValid_Invalid_Col) {
    Position pos(5, 15);
    EXPECT_FALSE(pos.isValid());
}

TEST(PositionTest, EqualityOperator) {
    Position p1(3, 4);
    Position p2(3, 4);
    Position p3(4, 3);
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
}


TEST(ShipTest, DefaultConstructor) {
    Ship ship;
    EXPECT_EQ(ship.getSize(), 2);
    EXPECT_FALSE(ship.isSunk());
}

TEST(ShipTest, ParameterizedConstructor_Horizontal) {
    Position start(2, 3);
    Ship ship(4, start, true);
    EXPECT_EQ(ship.getSize(), 4);
    EXPECT_TRUE(ship.getIsHorizontal());
    EXPECT_EQ(ship.getStart().getRow(), 2);
    EXPECT_EQ(ship.getStart().getCol(), 3);
}

TEST(ShipTest, ParameterizedConstructor_Vertical) {
    Position start(1, 1);
    Ship ship(3, start, false);
    EXPECT_FALSE(ship.getIsHorizontal());
}

TEST(ShipTest, GetPositions_Horizontal) {
    Position start(0, 0);
    Ship ship(3, start, true);
    std::vector<Position> positions = ship.getPositions();
    EXPECT_EQ(positions.size(), 3);
    EXPECT_EQ(positions[0], Position(0, 0));
    EXPECT_EQ(positions[1], Position(0, 1));
    EXPECT_EQ(positions[2], Position(0, 2));
}

TEST(ShipTest, GetPositions_Vertical) {
    Position start(0, 0);
    Ship ship(3, start, false);
    std::vector<Position> positions = ship.getPositions();
    EXPECT_EQ(positions.size(), 3);
    EXPECT_EQ(positions[0], Position(0, 0));
    EXPECT_EQ(positions[1], Position(1, 0));
    EXPECT_EQ(positions[2], Position(2, 0));
}

TEST(ShipTest, OccupiesPosition) {
    Position start(5, 5);
    Ship ship(3, start, true);
    EXPECT_TRUE(ship.occupiesPosition(Position(5, 5)));
    EXPECT_TRUE(ship.occupiesPosition(Position(5, 7)));
    EXPECT_FALSE(ship.occupiesPosition(Position(5, 8)));
    EXPECT_FALSE(ship.occupiesPosition(Position(6, 5)));
}

TEST(ShipTest, TakeHit_NotSunk) {
    Position start(0, 0);
    Ship ship(3, start, true);
    ship.takeHit(Position(0, 0));
    EXPECT_FALSE(ship.isSunk());
}

TEST(ShipTest, TakeHit_Sunk) {
    Position start(0, 0);
    Ship ship(2, start, true);
    ship.takeHit(Position(0, 0));
    ship.takeHit(Position(0, 1));
    EXPECT_TRUE(ship.isSunk());
}


TEST(GameFieldTest, Constructor_EmptyField) {
    GameField field;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_EQ(field.getCellState(Position(i, j)), EMPTY);
        }
    }
}

TEST(GameFieldTest, PlaceShip_Success) {
    GameField field;
    Ship ship(3, Position(0, 0), true);
    EXPECT_TRUE(field.placeShip(ship));
    EXPECT_EQ(field.getCellState(Position(0, 0)), SHIP);
    EXPECT_EQ(field.getCellState(Position(0, 1)), SHIP);
    EXPECT_EQ(field.getCellState(Position(0, 2)), SHIP);
}

TEST(GameFieldTest, PlaceShip_OutOfBounds) {
    GameField field;
    Ship ship(3, Position(0, 8), true);  
    EXPECT_FALSE(field.placeShip(ship));
}

TEST(GameFieldTest, PlaceShip_Overlap) {
    GameField field;
    Ship ship1(3, Position(0, 0), true);
    Ship ship2(2, Position(0, 2), true);  
    EXPECT_TRUE(field.placeShip(ship1));
    EXPECT_FALSE(field.placeShip(ship2));
}

TEST(GameFieldTest, Shoot_Miss) {
    GameField field;
    EXPECT_FALSE(field.shoot(Position(5, 5)));
    EXPECT_EQ(field.getCellState(Position(5, 5)), MISS);
}

TEST(GameFieldTest, Shoot_Hit) {
    GameField field;
    Ship ship(3, Position(0, 0), true);
    field.placeShip(ship);
    EXPECT_TRUE(field.shoot(Position(0, 1)));
    EXPECT_EQ(field.getCellState(Position(0, 1)), HIT);
}

TEST(GameFieldTest, Shoot_AlreadyShot) {
    GameField field;
    field.shoot(Position(3, 3));
    EXPECT_FALSE(field.shoot(Position(3, 3))); 
}

TEST(GameFieldTest, AllShipsSunk) {
    GameField field;
    Ship ship(2, Position(0, 0), true);
    field.placeShip(ship);
    EXPECT_FALSE(field.allShipsSunk());

    field.shoot(Position(0, 0));
    field.shoot(Position(0, 1));
    EXPECT_TRUE(field.allShipsSunk());
}


TEST(PlayerTest, Constructor) {
    Player player("TestPlayer");
    EXPECT_EQ(player.getName(), "TestPlayer");
    EXPECT_EQ(player.getShotsFired(), 0);
    EXPECT_EQ(player.getHitsMade(), 0);
}

TEST(PlayerTest, PlaceShip) {
    Player player("P1");
    Ship ship(3, Position(0, 0), true);
    EXPECT_TRUE(player.placeShip(ship));
}

TEST(PlayerTest, ShootAt_Miss) {
    Player player("P1");
    GameField enemyField;
    EXPECT_FALSE(player.shootAt(enemyField, Position(5, 5)));
    EXPECT_EQ(player.getShotsFired(), 1);
    EXPECT_EQ(player.getHitsMade(), 0);
}

TEST(PlayerTest, ShootAt_Hit) {
    Player player("P1");
    GameField enemyField;
    Ship ship(2, Position(0, 0), true);
    enemyField.placeShip(ship);

    EXPECT_TRUE(player.shootAt(enemyField, Position(0, 0)));
    EXPECT_EQ(player.getShotsFired(), 1);
    EXPECT_EQ(player.getHitsMade(), 1);
}

TEST(PlayerTest, GetAccuracy) {
    Player player("P1");
    GameField enemyField;
    Ship ship(2, Position(0, 0), true);
    enemyField.placeShip(ship);

    player.shootAt(enemyField, Position(0, 0)); 
    player.shootAt(enemyField, Position(5, 5)); 
    player.shootAt(enemyField, Position(0, 1)); 

    EXPECT_DOUBLE_EQ(player.getAccuracy(), 2.0 / 3.0 * 100.0);
}



TEST(GameTest, Constructor) {
    Game game("Player1", "Player2");
    EXPECT_EQ(game.getCurrentPlayer().getName(), "Player1");
    EXPECT_FALSE(game.isGameOver());
}

TEST(GameTest, SetupShips) {
    Game game("P1", "P2");
    game.setupShips();
    EXPECT_FALSE(game.getCurrentPlayer().getField().allShipsSunk());
    EXPECT_FALSE(game.getOtherPlayer().getField().allShipsSunk());
}

TEST(GameTest, MakeMove_SwitchPlayer) {
    Game game("P1", "P2");
    game.setupShips();

    EXPECT_EQ(game.getCurrentPlayer().getName(), "P1");
    game.makeMove(Position(0, 0));
    game.switchPlayer();
    EXPECT_EQ(game.getCurrentPlayer().getName(), "P2");
}

TEST(GameTest, GameOver_WhenAllShipsSunk) {
    Game game("P1", "P2");
    game.setupShips();

    std::vector<Position> allShipPositions = {
        Position(0, 5), Position(0, 6), Position(0, 7), Position(0, 8), Position(0, 9),
        Position(2, 5), Position(2, 6), Position(2, 7), Position(2, 8),
        Position(4, 5), Position(4, 6), Position(4, 7),
        Position(5, 5), Position(5, 6), Position(5, 7),
        Position(7, 5), Position(7, 6),
        Position(8, 5), Position(8, 6)
    };

    for (const Position& pos : allShipPositions) {
        EXPECT_FALSE(game.isGameOver());
        game.makeMove(pos);
    }


    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getWinner()->getName(), "P1");
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}