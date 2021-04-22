#include "cycle.h"
#include "graph.h"
#include "astar.h"

// DEBUG
#include <iostream>

using namespace std;

Cycle::Cycle( const Playfield *pf )
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

	Graph *G = new Graph( grid );

	// ***** SUBROUTINE build the heuristic
	map<int, double> heuristic;
	for( int v : G->Vertices( ) )
		heuristic[v] = 1;

	if( pf->getTail( ).size( ) <= 3 )
	{
		AStar findFood( G, headNode, foodNode, heuristic );
		return;
	}


	// ***** SUBROUTINE Establish Master Cycle ( EMC )

	grid[tail.first][tail.second] = CLEAR_VALUE; // handle snake of size < 3
	AStar headtotail( G, headNode, tailNode, heuristic );

	// update the graph for path taken to tail and pop off the tail nodes ( tail management )
	//delete G;
	//Graph *G = new Graph( grid );
	AStar tailtofood( G, tailNode, foodNode, heuristic );

	// update the graph for path taken to the food and pop off the tail nodes ( tail mangement )
	//delete G;
	//Graph *G = new Graph( grid );
	AStar foodtohead( G, foodNode, headNode, heuristic );

	delete G; // Memory Management


	// ***** SUBROUTINE Establish Master Path ( EMP )

	pushPath( headtotail.pathTo( tailNode ) );
	pushPath( tailtofood.pathTo( foodNode ) );
	pushPath( foodtohead.pathTo( headNode ) );


	// DEBUG
	for( int n : path )
		cout << n << ' ';
	cout << endl;
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
