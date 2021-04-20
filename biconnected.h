/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef BICONNECTED_H
#define BICONNECTED_H
#include <algorithm>
#include "snakeGraph.h"

#define NO_PARENT -1
/********************************************************************//**
 * @class Biconnected
 * 
 * Find articulation nodes in a graph.  This is used when a grid with
 * obstacles is generated to verify that the field is 'solvable'.  Any
 * graph representing a grid with obstacles is not solvable if there are
 * any articulation nodes
 **********************************************************************/
class Biconnected
{
   std::map<int, bool> visited;
   std::map<int, int> time;
   std::map<int, int> loTime;
   std::map<int, int> parent;
   std::set<int> articulationPoints;
   int Time;
public:
   Biconnected(SnakeGraph *G);

   std::set<int> articulationNodes();
private:
   void dfs(SnakeGraph *, int); 
};
#endif
