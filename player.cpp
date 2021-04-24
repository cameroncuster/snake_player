/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "cycle.h"

using namespace std;

Player::Player( ) { }

// determine the move to make
ValidMove nextMove( int w, int s, int n )
{
	ValidMove move = NONE;
	const int delta[4] = { -w, 1, w, -1 };
	for( int i = 0; i < 4; i++ )
		if( s + delta[i] == n )
		{
			if( i == 0 ) move = UP;
			if( i == 1 ) move = RIGHT;
			if( i == 2 ) move = DOWN;
			if( i == 3 ) move = LEFT;
		}
	return move;
}

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
