/********************************************************************//**
 * @file
 ***********************************************************************/
#include "simulatefield.h"

Simulatefield::Simulatefield( const Playfield *pf, std::queue<std::pair<int, int>> t ) : tail( t )
{
        head = pf->headPosition( );
        food = pf->foodPosition( );
        grid = pf->getGrid( );
        width = grid[0].size( );
        height = grid.size( );
        hasObstacles = 0;
        tailLength = pf->getScore( ) - 1;
        for( vector<int> v : grid )
            for( int x : v )
                if( x == OBSTACLE_VALUE )
                    hasObstacles = 1;
}

Simulatefield::Simulatefield( const Simulatefield *pf )
{
    head = pf->head;
    food = pf->food;
    tail = pf->tail;
    width = pf->width;
    height = pf->height;
    hasObstacles = pf->hasObstacles;
    tailLength = pf->tailLength;
    grid = pf->grid;
}

// Getter functions
std::pair<int, int> Simulatefield::headPosition() const { return head; }
std::pair<int, int> Simulatefield::foodPosition() const { return food; }
std::vector<std::vector<int>> Simulatefield::getGrid() const { return grid ; }
std::queue<std::pair<int, int>> Simulatefield::getTail() const
{
   std::queue<std::pair<int,int>> first;
   first.push( head );
   return tail.empty() ? first : tail;
}
int Simulatefield::getScore() const { return tailLength + 1; }

// Helper function: Clear the grid initially
void Simulatefield::clearGrid()
{
   for (int y = 0 ; y < height ; y++)
      for (int x = 0 ; x < width ; x++)
        grid[y][x] = CLEAR_VALUE;
}

Simulatefield::~Simulatefield() {}

// Place obstacles on the playfield if requested
void Simulatefield::placeObstacles()
{
   if (!hasObstacles) return;
   int obstacleCount = 0.05 * width * height;

   while (obstacleCount--)
   {
      int x, y;
      do
      {
         x = rand() % width;
         y = rand() % height;
      } while (grid[y][x] != CLEAR_VALUE);
      grid[y][x] = OBSTACLE_VALUE;
   }
}

// clean up after the tail once it has passed
void Simulatefield::updatePlayfield()
{
   while (tailLength < tail.size())
   {
      std::pair<int, int> segment = tail.front() ; tail.pop();
      grid[segment.first][segment.second] = CLEAR_VALUE;
   }
}

// Calculate a new head position based on the current head position + a move
std::pair<int, int> Simulatefield::translateHead(ValidMove move)
{
   return std::make_pair(head.first + translate[move].first,
                         head.second + translate[move].second);
}

// Once the food is consumed, place a new food randomly in an open space
// Optimization: Only randomly select from open spaces
std::pair<int, int> Simulatefield::placeNewFood()
{
   int x, y;
   do
   {
      x = rand() % width;
      y = rand() % height;
   } while (grid[y][x] != CLEAR_VALUE);
   grid[y][x] = FOOD_VALUE;
   return std::pair<int, int>(y, x);
}

// Given a player move, attempt to move the head in that direction
// Return false if the move hits the tail or other obstacle
// otherwise return true, move the head, update the tail
bool Simulatefield::moveHead(ValidMove move)
{
   // moves of 'NONE' end the game
   if (move == NONE) return false;

   std::pair<int, int> newHeadPosition = translateHead(move);

   if (OutOfBounds(newHeadPosition))
      return false;

   // Look at the destination cell to see if it's valid
   int val = grid[newHeadPosition.first][newHeadPosition.second];
   if (val == TAIL_VALUE || val == OBSTACLE_VALUE)
   {
      grid[newHeadPosition.first][newHeadPosition.second] = COLLISION_VALUE;
      return false;
   }

   // If the destination cell is the food, grow the tail and
   // place a new food.
   if (newHeadPosition == food)
   {
      tailLength++;
      food = placeNewFood();
   }

   // Put the head on the tail queue
   tail.push(head);
   // advance the tail into the old head position
   grid[head.first][head.second] = TAIL_VALUE;
   head = newHeadPosition;
   // advance the head into its new position
   grid[head.first][head.second] = HEAD_VALUE;
   return true;
}
