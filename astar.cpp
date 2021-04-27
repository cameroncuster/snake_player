/********************************************************************//**
 * @file
 ***********************************************************************/
#include <limits>
#include "astar.h"

using namespace std;

// heuristic must be instantiated for all nodes |V| or straightLineDistance will
    // be nullified
AStar::AStar( Graph *G, int s, int f, map<int, double> h ) : start( s ),
    finish( f ), columns( G->Columns( ) )
{
    heuristic = h;
    for( int v : G->Vertices( ) )
        dist[v] = numeric_limits<int>::max( );

    dist[start] = 0.0;
    heap.push( Node( start, straightLineDistance( start ) + heuristic[start] ) );
    while( !heap.empty( ) )
    {
        Node node = heap.top( );
        heap.pop( );
        for( int w : G->adj( node.vertex ) )
            relax( node.vertex, w, G );
    }
}

bool AStar::hasPath( int v )
{
    return dist[v] != numeric_limits<int>::max( );
}

// path does not include start node
list<int> AStar::pathTo( int v )
{
    list<int> path;
    if( !hasPath( v ) )
        return path;

    for( int x = v; x != start; x = prev[x] )
        path.push_front( x );

    return path;
}

void AStar::relax( int v, int w, Graph *G )
{
    if( dist[w] > dist[v] + 1 )
    {
        dist[w] = dist[v] + 1;
        prev[w] = v;
        heap.push( Node( w, straightLineDistance( w ) + heuristic[w] ) );
    }
}

// manhattan distance with respect to what the grid represents (euclidian
// distance would not make sense)
int AStar::straightLineDistance( int w ) const
{
    int x = w % columns;
    int y = w / columns;
    int finishX = finish % columns;
    int finishY = finish / columns;
    return abs( finishY - y ) + abs( finishX - x );
}
