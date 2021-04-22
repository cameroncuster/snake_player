/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "astar.h"

#include <iostream>

using namespace std;

Player::Player( )
{
	headtail = 0;
	headfood = 1;
}

bool inBounds( const int w, const int h, const int i, const int j )
{
	return i >= 0 && i < h && j >= 0 && j < w;
}

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
	vector<std::vector<int>> grid = pf->getGrid();
	int w = grid[0].size( );
	int h = grid.size( );
	pair<int, int> head = pf->headPosition();
	pair<int, int> food = pf->foodPosition();
	pair<int, int> tail = pf->getTail().front();
	int headNode = head.first * w + head.second;
	int foodNode = food.first * w + food.second;
	int tailNode = tail.first * w + tail.second; // trying to search for node that is not in the graph

	grid[tail.first][tail.second] = CLEAR_VALUE; // handle snake of size 2

	if( !path.empty( ) )
	{
		int next = path.front( );
		path.pop_front( );
		return nextMove( w, headNode, next );
	}

	cout << "head " << headNode << endl;
	cout << "food " << foodNode << endl;
	cout << "tail " << tailNode << endl;
	cout << endl << endl;

	Graph *G = new Graph( grid );

	// build the heuristic
	map<int, double> heuristic;
	for( int v : G->Vertices( ) )
		heuristic[v] = 1;

	AStar headtotail( G, headNode, tailNode, heuristic );
	AStar headtofood( G, headNode, foodNode, heuristic );

	if( headtail ) // AStar head to tail
		pushPath( headtotail.pathTo( tailNode ) );
	else if( headfood ) // AStar head to food
		pushPath( headtofood.pathTo( foodNode ) );

	// DEBUG
	for( int n : path )
		cout << n << ' ';
	cout << endl;

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

	// flags
	if( pf->getTail( ).size( ) > 3 )
	{
		headtail = !headtail;
		headfood = !headfood;
	}

	delete G; // memory clean-up

	// determine the move to make
	int next = path.front( );
	path.pop_front( );
	return nextMove( w, headNode, next );
}

void Player::pushPath( list<int> p )
{
	if( !p.empty( ) ) p.pop_front( ); // end of last path == start of next path
	for( int n : p )
		path.push_back( n );
}
