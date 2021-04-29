/********************************************************************//**
 * @file
 ***********************************************************************/
#include "playfield.h"

// Copy constructor for running alternate games (GA players)
// Create a playfield from a const Playfield pointer
Playfield::Playfield(const Playfield *pf)
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

// Construct the playfield based on:
//
// int w  : width in cells
// int h  : height in cells
// bool ob: whether or not to place obstacles on the playfield
//
Playfield::Playfield(int w, int h, bool ob) : width(w), height(h), hasObstacles(ob), tailLength(0)
{
   srand(time(NULL));

   // Place the head and first food on the playfield
   head = std::pair<int, int>(rand() % height, rand() % width);
   food = std::pair<int, int>(rand() % height, rand() % width);

   int count;

   // Expand the grid to match the height and width
   grid.resize(height);
   for (int y = 0 ; y < height ; y++)
      grid[y].resize(width);

   if (hasObstacles)
   {
      std::cout << "Placing obstacles " << " and verifying solvability" 
                << std::endl;
      std::cout << "this may take a few seconds." << std::endl;
   }

   // 1. Clear the grid
   // 2. Place obstacles if requested
   // 3. Check that the grid is solvable
   do
   {
      clearGrid();
      placeObstacles();
      SnakeGraph graph(grid);
      Biconnected bicon(&graph);
      CC cc(&graph);
      count = cc.count() + bicon.articulationNodes().size();
   } while (count > 1);

   // Place the head and the food and update the playfield
   grid[head.first][head.second] = HEAD_VALUE;
   grid[food.first][food.second] = FOOD_VALUE;
   updatePlayfield();
}

// Getter functions
std::pair<int, int> Playfield::headPosition() const { return head; }
std::pair<int, int> Playfield::foodPosition() const { return food; }
std::vector<std::vector<int>> Playfield::getGrid() const { return grid ; }
int Playfield::getScore() const { return tailLength + 1; }

// Helper function: Clear the grid initially
void Playfield::clearGrid()
{
   for (int y = 0 ; y < height ; y++)
      for (int x = 0 ; x < width ; x++)
        grid[y][x] = CLEAR_VALUE;
}

Playfield::~Playfield() {}

// Place obstacles on the playfield if requested
void Playfield::placeObstacles()
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
void Playfield::updatePlayfield()
{
   while (tailLength < tail.size())
   {
      std::pair<int, int> segment = tail.front() ; tail.pop();
      grid[segment.first][segment.second] = CLEAR_VALUE;
   }
}

// Calculate a new head position based on the current head position + a move
std::pair<int, int> Playfield::translateHead(ValidMove move)
{
   return std::make_pair(head.first + translate[move].first,
                         head.second + translate[move].second);
}

// Once the food is consumed, place a new food randomly in an open space
// Optimization: Only randomly select from open spaces
std::pair<int, int> Playfield::placeNewFood()
{
   std::vector<std::pair<int, int>> spots;
   for (int row = 0 ; row < height ; row++)
      for (int col = 0 ; col < width ; col++)
         if (grid[row][col] == CLEAR_VALUE) 
            spots.push_back(std::make_pair(row,col));

   if (spots.size() > 0) 
   {
      std::pair<int, int> choice = spots[rand() % spots.size()];
      grid[choice.first][choice.second] = FOOD_VALUE;
      return choice;
   }
   return invalid_food_location;
}

// Given a player move, attempt to move the head in that direction
// Return false if the move hits the tail or other obstacle
// otherwise return true, move the head, update the tail
bool Playfield::moveHead(ValidMove move)
{
   // moves of 'NONE' end the game
   if (move == NONE) return false;

   std::pair<int, int> newHeadPosition = translateHead(move);

   if (OutOfBounds(newHeadPosition))
   {
      std::cout << "Ran into boundary" << std::endl;
      return false;
   }

   // Look at the destination cell to see if it's valid
   int val = grid[newHeadPosition.first][newHeadPosition.second];
   if (val == TAIL_VALUE || val == OBSTACLE_VALUE)
   {
      std::cout << "Ran into ";
      if (val == TAIL_VALUE) std::cout << "Tail";
      if (val == OBSTACLE_VALUE) std::cout << "Obstacle";
      std::cout << std::endl;
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
   return (food != invalid_food_location);
}
