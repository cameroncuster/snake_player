/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef SNAKEGRAPH_H
#define SNAKEGRAPH_H
#include <map>
#include <set>
#include <vector>
#include "defines.h"

/********************************************************************//**
 * @class SnakeGraph
 * 
 * Generic Graph class renamed to prevent name space collisions with
 * player code.  Yes, this could be put into its own namespace but
 * we still run the risk of file name collisions
 **********************************************************************/
class SnakeGraph
{
   std::map<int, std::set<int>> vertices;
   int numVertices, numEdges;
public:
   SnakeGraph(std::vector<std::vector<int>> &);
  
   std::set<int> Vertices() const;
   std::set<int> adj(int);
   int V() const;
   int E() const;
private:
   void addEdge(int, int);
};
#endif
