/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef CC_H
#define CC_H
#include <queue>
#include "snakeGraph.h"

/********************************************************************//**
 * @class Cc
 *
 * Count the connected components in a graph.  This is used to help
 * verify that a grid is 'solvable'.  If there are multiple connected
 * components then the grid is not solvable.
 **********************************************************************/
class CC
{
   std::map<int, bool> marked;
   std::map<int, int> cc;
   int ccount;
public:
   CC(SnakeGraph *G);

   bool connected(int v, int w);
   int count() const;
   int id(int v);
private:
   void bfs(SnakeGraph *, int);
};
#endif
