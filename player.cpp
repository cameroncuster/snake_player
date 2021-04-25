/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "cycle.h"

using namespace std;

extern ValidMove nextMove( int, int, int );
extern bool inBounds( const int w, const int h, const int i, const int j );

Player::Player( ) { }

ValidMove Player::makeMove( const Playfield *pf )
{
	vector<vector<int>> grid = pf->getGrid();
	int w = grid[0].size( );
	int h = grid.size( );
	queue<pair<int, int>> tail = pf->getTail();
	pair<int, int> head = pf->headPosition();
	pair<int, int> food = pf->foodPosition();
	pair<int, int> tailpt = tail.front();
	int headNode = head.first * w + head.second;
	int foodNode = food.first * w + food.second;
	int tailNode = tailpt.first * w + tailpt.second;

	if( path.empty( ) )
	{
		Cycle c( pf );
		path = c.cycle( );
		// check if a path exists - scan otherwise
		if( path.empty( ) )
		{
			if( inBounds( w, h, head.first - 1, head.second ) )
				if( !grid[head.first - 1][head.second] )
					return UP;

			if( inBounds( w, h, head.first, head.second + 1 ) )
				if( !grid[head.first][head.second + 1] )
					return RIGHT;

			if( inBounds( w, h, head.first + 1, head.second ) )
				if( !grid[head.first + 1][head.second] )
					return DOWN;

			if( inBounds( w, h, head.first, head.second - 1 ) )
				if( !grid[head.first][head.second - 1] )
					return LEFT;
		}

	}
	int n = path.front( );
	path.pop_front( );
	return nextMove( pf->getGrid( )[0].size( ),
			pf->headPosition( ).first * pf->getGrid( )[0].size( ) +
			pf->headPosition( ).second, n );
}
