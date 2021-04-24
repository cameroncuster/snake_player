#include <iostream>
#include <vector>
#include "defines.h"

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
