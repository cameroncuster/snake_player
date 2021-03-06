/********************************************************************//**
 * @file
 ***********************************************************************/
#include "cycle.h"
#include "graph.h"
#include "astar.h"
#include "simulation.h"

extern bool inBounds( const int, const int, const int, const int );
extern ValidMove nextMove( int, int, int );

static const std::vector<std::vector<int>> delta =
{ { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

// Develop a cycle with the following algorithm:
// 1. find food
// 2. return to tail from food
// 3. if either (1) or (2) is impossible then follow the tail
// Heuristic function to coil the snake did not improve performance with
    // A* graph traversal
Cycle::Cycle( const Playfield *pf, std::queue<std::pair<int, int>> tail )
{
    int width = pf->getGrid( )[0].size( );
    std::pair<int, int> head = pf->headPosition();
    std::pair<int, int> food = pf->foodPosition();
    int headNode = head.first * width + head.second;
    int foodNode = food.first * width + food.second;

    // small snakes find food
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

    delete G;

    // simulate moves
    Simulatefield *sim = new Simulatefield( pf, tail );
    Simulation simulateMoves( sim, path );

    if( pathAround( sim->getGrid( ), sim->headPosition( ),
                sim->getTail( ).front( ) ) )
    {
        delete sim;
        return;
    }

    delete sim;

    // clear the path and follow the tail
    path.clear( );
    pathAround( pf->getGrid( ), pf->headPosition( ), tail.front( ) );
}

std::list<int> Cycle::cycle( ) const { return path; }

bool Cycle::pushPath( const std::list<int> p )
{
    if( p.empty( ) ) return 0;
    for( int n : p ) path.push_back( n );
    return 1;
}

// Locate a path to node adjacent to the tail, append the path to the tail and
    // return success
bool Cycle::pathAround( std::vector<std::vector<int>> grid,
        std::pair<int, int> source, std::pair<int, int> dest )
{
    bool free = 0;
    int width = grid[0].size( );
    int height = grid.size( );
    for( int i = 0; i < 4 && !free; i++ )
    {
        std::pair<int, int> extend = { dest.first + delta[i][0],
            dest.second + delta[i][1] };
        if( inBounds( width, height, extend.first, extend.second ) )
            if( grid[ extend.first ][ extend.second ] == CLEAR_VALUE )
            {
                int extendNode = extend.first * width + extend.second;

                // search to tail
                Graph *G = new Graph( grid );
                AStar findTail( G, source.first * width + source.second,
                        extendNode );

                // clean up
                delete G;

                // push the path and return false if empty
                free = pushPath( findTail.pathTo( extendNode ) );
            }
    }
    return free;
}
