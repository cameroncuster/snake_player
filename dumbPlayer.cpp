/********************************************************************//**
 * @file
 ***********************************************************************/
#include "player.h"

Player::Player() { }

// Simple snake driver which attempts to move the head in the general direction
// of the food.  It does not avoid its own tail or obstacles in the playfield
ValidMove Player::makeMove(const Playfield *pf)
{
   std::vector<std::vector<int>> grid = pf->getGrid();
   std::pair<int, int> head = pf->headPosition();
   std::pair<int, int> food = pf->foodPosition();

   int dY = head.first - food.first;
   int dX = head.second - food.second;

   if (dX == 0) // in the correct column
   {
      if (dY > 0) // Above the food
         return UP;
      else
         return DOWN;
   }
   else // Not in the correct column
   { 
      if (dX > 0) // I'm to the right of the food
         return LEFT;
      else // I'm to the left of the food
         return RIGHT;
   }
   return NONE;
}
