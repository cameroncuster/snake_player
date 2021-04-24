/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "cycle.h"

using namespace std;

extern ValidMove nextMove( int, int, int );

Player::Player( ) { }

ValidMove Player::makeMove( const Playfield *pf )
{
	if( path.empty( ) )
	{
		Cycle c( pf );
		path = c.cycle( );
	}
    int n = path.front( );
    path.pop_front( );
	return nextMove( pf->getGrid( )[0].size( ),
			pf->headPosition( ).first * pf->getGrid( )[0].size( ) +
			pf->headPosition( ).second, n );
}
