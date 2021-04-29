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
    vector<vector<int>> grid = pf->getGrid();
    int w = grid[0].size( );
    int h = grid.size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    pair<int, int> tailpt = tail.front();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;
    int tailNode = tailpt.first * w + tailpt.second;

    if( tail.size( ) <= 3 )
    {
        Graph *G = new Graph( grid );
        Heuristic heuristic( pf->getGrid( ), G->Vertices( ) );
        AStar findFood( G, headNode, foodNode, heuristic.get( ) );
        path = findFood.pathTo( foodNode );
        delete G;
        return;
    }

    Simulatefield *sim = new Simulatefield( pf, tail );

    Graph *G = new Graph( grid );

    Heuristic *heuristic = new Heuristic( sim->getGrid( ), G->Vertices( ) );

    AStar findFood( G, headNode, foodNode, heuristic->get( ) );
    delete G;
    delete heuristic;

    path = findFood.pathTo( foodNode );

    Simulation simulateMoves( sim, path );

    bool free = 0;
    for( int i = 0; i < 4; i++ )
    {
        pair<int, int> tailExtend = { sim->getTail( ).front( ).first + delta[i][0], sim->getTail( ).front( ).second + delta[i][1] };
        if( inBounds( w, h, tailExtend.first, tailExtend.second ) )
            if( sim->getGrid( )[tailExtend.first][tailExtend.second] == CLEAR_VALUE )
            {
                tailNode = tailExtend.first * w + tailExtend.second;

                G = new Graph( sim->getGrid( ) );

                heuristic = new Heuristic( sim->getGrid( ), G->Vertices( ) );

                // search to tail
                AStar findTail( G, sim->headPosition( ).first * w + sim->headPosition( ).second, tailNode, heuristic->get( ) );
                delete G;
                delete heuristic;

                if( findTail.hasPath( tailNode ) )
                {
                    free = pushPath( findTail.pathTo( tailNode ) );
                    break;
                }
            }
    }

    delete sim;

    if( !free )
    {
        // reset locals & search to tail
        /*
        grid = pf->getGrid();
        head = pf->headPosition();
        food = pf->foodPosition();
        tailpt = tail.front();
        headNode = head.first * w + head.second;
        foodNode = food.first * w + food.second;
        tailNode = tailpt.first * w + tailpt.second;
        */

        for( int i = 0; i < 4; i++ )
        {
            pair<int, int> tailExtend = { tail.front( ).first + delta[i][0], tail.front( ).second + delta[i][1] };
            if( inBounds( w, h, tailExtend.first, tailExtend.second ) )
                if( grid[tailExtend.first][tailExtend.second] == CLEAR_VALUE )
                {
                    tailNode = tailExtend.first * w + tailExtend.second;

                    G = new Graph( grid );

                    heuristic = new Heuristic( pf->getGrid( ), G->Vertices( ) );

                    AStar follow( G, headNode, tailNode, heuristic->get( ) );

                    delete G;
                    delete heuristic;

                    if( follow.hasPath( tailNode ) )
                    {
                        path = follow.pathTo( tailNode ); // reassign
                        break;
                    }
                }
        }
    }
}

list<int> Cycle::cycle( ) const { return path; }

bool Cycle::pushPath( const list<int> p )
{
    if( p.empty( ) ) return 0;
    for( int n : p ) path.push_back( n );
    return 1;
}
