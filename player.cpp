/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "astar.h"

#include <iostream>

using namespace std;

Player::Player() { }

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
	int tailNode = tail.first * w + tail.second;

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

	// body is on the graph e.a. handled by the search

	// AStar head to tail
	AStar headtotail( G, headNode, tailNode, heuristic );

	// place the body on the graph before search

	// AStar tail to food
	AStar tailtofood( G, tailNode, foodNode, heuristic );

	// place the body on the graph before search

	// AStar food to tail
	AStar foodtotail( G, foodNode, headNode, heuristic ); // maybe newTailNode/oldHead location

	/// Establish master path

	// path to tail
	pushPath( headtotail.pathTo( tailNode ) );

	// path to food
	pushPath( tailtofood.pathTo( foodNode ) );

	// path to newtail
	pushPath( foodtotail.pathTo( headNode ) );

	// DEBUG
	for( int n : path )
		cout << n << ' ';
	cout << endl;

	if( path.empty( ) )
	{
		// handle path not existing
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
