#include "cycle.h"
#include "graph.h"
#include "astar.h"
#include "heuristic.h"

// DEBUG
#include <iostream>

using namespace std;

list<pair<int, int>> pathtoPoint( int w, list<int> path )
{
	list<pair<int, int>> pointlist;

	for( int n : path )
		pointlist.push_back( { n / w, n % w } );

	return pointlist;
}

void updateGrid( vector<vector<int>> &grid, list<pair<int, int>> path,
		queue<pair<int, int>> &tail, pair<int, int> &head )
{
	// need to check if apple is encountered
	while( !path.empty( ) )
	{
		// move head
		grid[head.first][head.second] = TAIL_VALUE;
		head = path.front( );

		if( grid[head.first][head.second] != FOOD_VALUE )
		{
			// move tail
			grid[ tail.front( ).first ][ tail.front( ).second ] = CLEAR_VALUE;
			tail.pop( );
		}

		grid[head.first][head.second] = HEAD_VALUE;

		tail.push( head );
		// continue path
		path.pop_front( );
	}
}

Cycle::Cycle( const Playfield *pf )
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

	if( pf->getTail( ).size( ) <= 3 )
	{
		Graph *G = new Graph( grid );
		Heuristic heuristic( G->Vertices( ) );
		AStar findFood( G, headNode, foodNode, heuristic.get( ) );
		path = findFood.pathTo( foodNode );
		delete G;
		return;
	}

	// set the graph to have a clear value here
	grid[tailpt.first][tailpt.second] = CLEAR_VALUE;
	Graph *G = new Graph( grid );

	Heuristic heuristic( G->Vertices( ) );

	AStar findFood( G, headNode, foodNode, heuristic.get( ) );

	// push the path to food
	pushPath( findFood.pathTo( foodNode ) );

	// move head to food
	updateGrid( grid, pathtoPoint( w, findFood.pathTo( foodNode ) ), tail, head );

	// set the headNode/tailNode
	tailpt = tail.front( );
	tailNode = tailpt.first * w + tailpt.second;
	headNode = head.first * w + head.second;

	// search to tail
	AStar findTail( G, headNode, tailNode, heuristic.get( ) );

	// push the path to the tail
	pushPath( findTail.pathTo( tailNode ) );

	/// DBEUG
	// Update Grid
	updateGrid( grid, pathtoPoint( w, findTail.pathTo( tailNode ) ), tail, head );

	// DEBUG
	for( vector<int> v : grid )
	{
		for( int x : v )
			cout << x << ' ';
		cout << endl;
	}
	cout << endl << endl;


	delete G; // Memory Management
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
