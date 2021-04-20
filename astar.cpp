#include <limits>
#include "astar.h"

using namespace std;

AStar::AStar( Graph *, int, int ) : start( s ), finish( f )
{
    for( int v : G->Vertices( ) )
        dist[v] = numeric_limits<int>::max( );

    dist[start] = 0.0;
    heap.push( Node( start, straightLineDistance( start, finish, G->Columns( ) ) ) );
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

list<int> AStar::pathTo( int v )
{
    list<int> path;
    if( !hasPath( v ) )
        return path;

    for( int x = v; x != start; x = prev[x] )
        path.push_front( x );

    path.push_front( start );
    return path;
}

void AStar::relax( int, int, Graph * )
{
    if( dist[w] > dist[v] + 1 )
    {
        dist[w] = dist[v] + 1;
        prev[w] = v;
        heap.push( Node( w, straightLineDistance( w, finish, G->Columns( ) ) ) );
    }
}
