/********************************************************************//**
 * @file
 ***********************************************************************/
#include "cc.h"

CC::CC(SnakeGraph *G) : ccount(0)
{
   for (int v : G->Vertices())
      if (!marked[v])
      {
         bfs(G, v);
         ccount++;
      }
}

void CC::bfs(SnakeGraph *G, int s)
{
   std::queue<int> q;
   q.push(s);
   marked[s] = true;
   while (!q.empty())
   {
      int v = q.front() ; q.pop();
      cc[s] = ccount;
      for (int w : G->adj(v))
         if (!marked[w])
         {
            q.push(w);
            marked[w] = true;
         }
   }
}

bool CC::connected(int v, int w)
{
   return (cc[v] == cc[w]);
}

int CC::count() const { return ccount ; }
int CC::id(int v) { return cc[v] ; }
