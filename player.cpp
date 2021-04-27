/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "cycle.h"

// DEBUG
#include <cassert>

using namespace std;

extern ValidMove nextMove( int, int, int );
extern bool inBounds( const int, const int, const int, const int );

Player::Player( ) { }

ValidMove Player::makeMove( const Playfield *pf )
{
    vector<vector<int>> grid = pf->getGrid();
    int w = grid[0].size( );
    int h = grid.size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    pair<int, int> tailpt = tail.empty( ) ? head : tail.front();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;
    int tailNode = tailpt.first * w + tailpt.second;

    queue<pair<int, int>> q;
    q.push( head );
    q = tail.empty( ) ? q : tail;
    assert( q == pf->getTail( ) );

    if( path.empty( ) )
    {
        Cycle c( pf, tail );
        path = c.cycle( );
    }
    int n = path.front( );
    path.pop_front( );

    tail.push( head );
    if( grid[n / w][n % w] != FOOD_VALUE ) tail.pop( );

    return nextMove( pf->getGrid( )[0].size( ),
            pf->headPosition( ).first * pf->getGrid( )[0].size( ) +
            pf->headPosition( ).second, n );
}
