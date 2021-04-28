/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "cycle.h"

extern ValidMove nextMove( int, int, int );
extern bool inBounds( const int, const int, const int, const int );

Player::Player( ) { }

// construct a cycle and follow the cycle (paths are cached)
ValidMove Player::makeMove( const Playfield *pf )
{
    // construct a cycle if the cached path is empty
    if( path.empty( ) )
    {
        Cycle c( pf, tail );
        path = c.cycle( );
    }
    int next = path.front( );
    path.pop_front( );

    // track my own tail
    tail.push( pf->headPosition( ) );
    if( pf->getGrid( )[next / pf->getGrid( )[0].size( )][next % pf->getGrid( )[0].size( )] != FOOD_VALUE ) tail.pop( );

    // translate the next point to a move to be executed
    return nextMove( pf->getGrid( )[0].size( ),
            pf->headPosition( ).first * pf->getGrid( )[0].size( ) +
            pf->headPosition( ).second, next );
}
