/********************************************************************//**
 * @file
 ***********************************************************************/
#include "inc/graph.h"

// Construct a graph from a vector<vector<int>> grid
Graph::Graph(std::vector<std::vector<int>> grid) : columns(grid.size())
{
    int height = grid.size();
    int width  = grid[0].size();

    for (int col = 0 ; col < width ; col++)
        for (int row = 0 ; row < height ; row++)
        {
            int index = row * width + col;
            if (!canEnter(row, col)) continue;
            if (vertices.find(index) == vertices.end())
                vertices[index] = std::set<int>{};
            if (canEnter(row+1, col)) addEdge(index, index+width);
            if (canEnter(row, col+1)) addEdge(index, index+1);
        }

    numVertices = vertices.size();
    numEdges = 0;
    for (int v : Vertices())
        numEdges += adj(v).size();

    numEdges /= 2;
}

int Graph::V() const { return numVertices ; }
int Graph::E() const { return numEdges ; }
int Graph::Columns() const { return columns ; }

std::set<int> Graph::Vertices() const
{
    std::set<int> retVal;
    for (auto &kv : vertices)
        retVal.insert(kv.first);

    return retVal;
}

std::set<int> Graph::adj(int v)
{
    return vertices[v];
}

void Graph::addEdge(int v, int w)
{
    vertices[v].insert(w);
    vertices[w].insert(v);
}
