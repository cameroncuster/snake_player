/********************************************************************//**
 * @file
 ***********************************************************************/
#include "biconnected.h"

Biconnected::Biconnected(SnakeGraph *G) : Time(0)
{
   for (int v : G->Vertices())
      parent[v] = NO_PARENT;

   dfs(G, *((G->Vertices()).begin()));
}

std::set<int> Biconnected::articulationNodes() { return articulationPoints ; }

void Biconnected::dfs(SnakeGraph *G, int v)
{
   int childCount = 0;
   bool isArticulation = false;

   visited[v] = true;
   time[v] = Time;
   loTime[v] = Time++;
   for (int w : G->adj(v))
   {
      if (w == parent[v]) continue;
      if (!visited[w])
      {
         parent[w] = v;
         childCount++;
         dfs(G, w);
         if (time[v] <= loTime[w])
            isArticulation = true;
         else
         {
            loTime[v] = std::min(loTime[v], loTime[w]);
         }
      }
      else
      {
         loTime[v] = std::min(time[w], loTime[v]);
      }
   }
   if ((parent[v] == NO_PARENT && childCount >= 2) ||
       (parent[v] != NO_PARENT && isArticulation))
      articulationPoints.insert(v);
}
