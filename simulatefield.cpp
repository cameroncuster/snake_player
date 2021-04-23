/********************************************************************//**
 * @file
 ***********************************************************************/
#include "simulatefield.h"

Simulatefield::Simulatefield( const Playfield *pf )
{
	head = pf->headPosition( );
	food = pf->foodPosition( );
	tail = pf->getTail( );
	grid = pf->getGrid( );
	width = grid[0].size( );
	height = grid.size( );
	hasObstacles = pf->obstacles( );
	tailLength = pf->getScore( ) - 1;
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
int Simulatefield::getScore() const { return tailLength + 1; }

// Helper function: Clear the grid initially
void Simulatefield::clearGrid()
{
   for (int y = 0 ; y < height ; y++)
      for (int x = 0 ; x < width ; x++)
        grid[y][x] = CLEAR_VALUE;
}

Simulatefield::~Simulatefield() {}

