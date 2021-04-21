/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <vector>
#include "defines.h"

/********************************************************************//**
 * @class Graph
 * 
 * Generic Graph class
 **********************************************************************/
class Graph
{
   std::map<int, std::set<int>> vertices;
   int numVertices, numEdges, columns;
public:
   Graph(std::vector<std::vector<int>> &);
  
   std::set<int> Vertices() const;
   std::set<int> adj(int);
   int V() const;
   int E() const;
   int Columns() const;
private:
   void addEdge(int, int);
};
#endif
