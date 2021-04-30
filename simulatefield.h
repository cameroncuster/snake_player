/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef SIMULATEFIELD_H
#define SIMULATEFIELD_H
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include "defines.h"
#include "biconnected.h"
#include "cc.h"
#include "playfield.h"
#include "cycle.h"

/********************************************************************//**
 * @class Simulatefield
 *
 * Manage the playfield simulation.
 **********************************************************************/
class Simulatefield
{
    // Private member data to implement Playfield object
    std::pair<int, int> head;
    std::pair<int, int> food;
    std::queue<std::pair<int, int>> tail;
    int width, height;
    bool hasObstacles;
    unsigned tailLength;
    std::vector<std::vector<int>> grid;
    public:
    Simulatefield( const Playfield *, std::queue<std::pair<int, int>> );
    Simulatefield( const Simulatefield * );
    ~Simulatefield();

    /// The current state of the playfield 2-d grid[y][x] y+ is down on screen
    std::vector<std::vector<int>> getGrid() const;
    /// Get the tail by coordinates
    std::queue<std::pair<int, int>> getTail() const;
    /// Get the current score, corresponds with the length of the tail
    int getScore() const;
    /// Current position of the head of the snake
    std::pair<int, int> headPosition() const;
    /// Current location of food on the grid
    std::pair<int, int> foodPosition() const;

    // allows the Simulation to simulate game play with private members
    friend class Simulation;

    private:
    void placeObstacles();
    void clearGrid();
    std::pair<int, int> translateHead(ValidMove);
    void updatePlayfield();
    bool moveHead(ValidMove);
};
#endif
