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
    int h = pf->getGrid( ).size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;
    int tailNode = tail.front( ).first * w + tail.front( ).second;

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

    bool free = 0;
    for( int i = 0; i < 4 && !free; i++ )
    {
        pair<int, int> tailExtend = { sim->getTail( ).front( ).first + delta[i][0], sim->getTail( ).front( ).second + delta[i][1] };
        if( inBounds( w, h, tailExtend.first, tailExtend.second ) )
            if( sim->getGrid( )[tailExtend.first][tailExtend.second] == CLEAR_VALUE )
            {
                tailNode = tailExtend.first * w + tailExtend.second;

                // search to tail
                G = new Graph( sim->getGrid( ) );
                AStar findTail( G, sim->headPosition( ).first * w + sim->headPosition( ).second, tailNode );

                // clean up
                delete G;

                free = pushPath( findTail.pathTo( tailNode ) );
            }
    }

    // clean up
    delete sim;

    if( free ) return;

    for( int i = 0; i < 4; i++ )
    {
        pair<int, int> tailExtend = { tail.front( ).first + delta[i][0], tail.front( ).second + delta[i][1] };
        if( inBounds( w, h, tailExtend.first, tailExtend.second ) )
            if( pf->getGrid( )[tailExtend.first][tailExtend.second] == CLEAR_VALUE )
            {
                tailNode = tailExtend.first * w + tailExtend.second;

                G = new Graph( pf->getGrid( ) );
                AStar follow( G, headNode, tailNode );

                delete G;

                if( follow.hasPath( tailNode ) )
                {
                    path = follow.pathTo( tailNode ); // reassign
                    break;
                }
            }
    }
    /*
    for( int i = 0; i < 4 && !free; i++ )
    {
        pair<int, int> tailExtend = { tail.front( ).first + delta[i][0], tail.front( ).second + delta[i][1] };
        if( inBounds( w, h, tailExtend.first, tailExtend.second ) )
            if( pf->getGrid( )[tailExtend.first][tailExtend.second] == CLEAR_VALUE )
            {
                tailNode = tailExtend.first * w + tailExtend.second;

                // search to tail
                G = new Graph( pf->getGrid( ) );
                AStar follow( G, headNode, tailNode );

                // clean up
                delete G;

                free = pushPath( follow.pathTo( tailNode ) );
            }
    }
    */
}

list<int> Cycle::cycle( ) const { return path; }

bool Cycle::pushPath( const list<int> p )
{
    if( p.empty( ) ) return 0;
    for( int n : p ) path.push_back( n );
    return 1;
}
