/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef __CYCLE_H
#define __CYCLE_H
#include <list>
#include <queue>
#include "playfield.h"

/********************************************************************//**
 * @class Cycle
 *
 * Develops a cycle for the snake to follow:
 * 1. Head to Food
 * 2. Food to Tail
 * 3. If 1 or 2 is not possible then Head to Tail
 * Traversals (SSSP) use A* with modified heuristic for performance
 **********************************************************************/
class Cycle
{
    std::list<int> path;
public:
    Cycle( const Playfield *, std::queue<std::pair<int, int>> );
    std::list<int> cycle( ) const;
private:
    bool pushPath( const std::list<int> );
    bool pathAround( std::vector<std::vector<int>> grid, int source, int dest );
};
#endif
