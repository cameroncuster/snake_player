/********************************************************************//**
 * @file
 ***********************************************************************/
#include "player.h"
#include "astar.h"

Player::Player() { }

// Scanner for simple 4 x 4 field to check for cases where final food can't
// be placed due to random not behaving
ValidMove Player::makeMove(const Playfield *pf)
{
   std::vector<std::vector<int>> grid = pf->getGrid();
   std::pair<int, int> head = pf->headPosition();

   std::vector<ValidMove> nextMove =
   {
      RIGHT, RIGHT, RIGHT, DOWN,
      UP, DOWN, LEFT, LEFT,
      UP, RIGHT, RIGHT, DOWN,
      UP, LEFT, LEFT, LEFT
   };

   int index = head.first * grid[0].size() + head.second;
   return nextMove[index];
}
