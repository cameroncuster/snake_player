/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include "defines.h"
#include "biconnected.h"
#include "cc.h"

/********************************************************************//**
 * @class Playfield
 * 
 * Manage the playfield
 **********************************************************************/

class Playfield
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
   Playfield(int, int, bool placeObst = false);
   Playfield(const Playfield *);
   ~Playfield();

   /// The current state of the playfield 2-d grid[y][x] y+ is down on screen
   std::vector<std::vector<int>> getGrid() const;
   /// Get the current score, corresponds with the length of the tail
   int getScore() const;
   /// Current position of the head of the snake
   std::pair<int, int> headPosition() const;
   /// Current location of food on the grid
   std::pair<int, int> foodPosition() const;

   // Private member functions used by Playfield and Game objects
   friend class Game;
private:
   void placeObstacles();
   void clearGrid();
   std::pair<int, int> placeNewFood();
   std::pair<int, int> translateHead(ValidMove);
   void updatePlayfield();
   bool moveHead(ValidMove);
};
#endif
