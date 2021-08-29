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
        if( path.empty( ) ) return NONE; // exit if no path can be found
    }
    int next = path.front( );
    path.pop_front( );

    // readability
    int width = pf->getGrid( )[0].size( );

    // track my own tail
    tail.push( pf->headPosition( ) );
    if( pf->getGrid( )[ next / width ][ next % width ] != FOOD_VALUE )
        tail.pop( );

    // translate the next point to a move to be executed
    return nextMove( width, pf->headPosition( ).first * width +
            pf->headPosition( ).second, next );
}
