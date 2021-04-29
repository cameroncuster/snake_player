/********************************************************************//**
 * @file
 ***********************************************************************/
#include "cycle.h"
#include "graph.h"
#include "astar.h"
#include "heuristic.h"
#include "simulation.h"

using namespace std;

extern bool inBounds( const int, const int, const int, const int );
extern ValidMove nextMove( int, int, int );

static const vector<vector<int>> delta = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

Cycle::Cycle( const Playfield *pf, queue<pair<int, int>> tail )
{
    int w = pf->getGrid( )[0].size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;

    if( tail.size( ) <= 3 )
    {
        Graph *G = new Graph( pf->getGrid( ) );
        AStar findFood( G, headNode, foodNode );
        path = findFood.pathTo( foodNode );
        delete G;
        return;
    }

    // path to food
    Graph *G = new Graph( pf->getGrid( ) );
    AStar findFood( G, headNode, foodNode );
    path = findFood.pathTo( foodNode );

    // clean up
    delete G;

    // simulate moves
    Simulatefield *sim = new Simulatefield( pf, tail );
    Simulation simulateMoves( sim, path );

    if( pathAround( sim->getGrid( ), sim->headPosition( ), sim->getTail( ).front( ) ) )
    {
        delete sim;
        return;
    }

    // clean up
    delete sim;

    path.clear( );
    pathAround( pf->getGrid( ), pf->headPosition( ), tail.front( ) );
}

list<int> Cycle::cycle( ) const { return path; }

bool Cycle::pushPath( const list<int> p )
{
    if( p.empty( ) ) return 0;
    for( int n : p ) path.push_back( n );
    return 1;
}

// Locate a path to node adjacent to the tail, append the path to the tail and return success
bool Cycle::pathAround( vector<vector<int>> grid, pair<int, int> source, pair<int, int> dest )
{
    bool free = 0;
    int w = grid[0].size( );
    int h = grid.size( );
    for( int i = 0; i < 4 && !free; i++ )
    {
        pair<int, int> extend = { dest.first + delta[i][0], dest.second + delta[i][1] };
        if( inBounds( w, h, extend.first, extend.second ) )
            if( grid[extend.first][extend.second] == CLEAR_VALUE )
            {
                int extendNode = extend.first * w + extend.second;

                // search to tail
                Graph *G = new Graph( grid );
                AStar findTail( G, source.first * w + source.second, extendNode );

                // clean up
                delete G;

                free = pushPath( findTail.pathTo( extendNode ) );
            }
    }
    return free;
}
