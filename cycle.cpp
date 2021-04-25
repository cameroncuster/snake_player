#include "cycle.h"
#include "graph.h"
#include "astar.h"
#include "heuristic.h"
#include "simulatefield.h"

using namespace std;

extern ValidMove nextMove( int, int, int );

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
	bool trap = 0;

	if( pf->getTail( ).size( ) <= 3 )
	{
		Graph *G = new Graph( grid );
		Heuristic heuristic( pf->getGrid( ), G->Vertices( ) );
		AStar findFood( G, headNode, foodNode, heuristic.get( ) );
		path = findFood.pathTo( foodNode );
		delete G;
		return;
	}

	Simulatefield sim( pf );

	Graph *G = new Graph( grid );

	Heuristic *heuristic = new Heuristic( sim.getGrid( ), G->Vertices( ) );

	AStar findFood( G, headNode, foodNode, heuristic->get( ) );
	delete G;
	delete heuristic;

	// check and push the path to food
	if( !findFood.hasPath( foodNode ) )
		trap = 1;
	path = findFood.pathTo( foodNode );

	// EXECUTE THE PATH TO THE FOOD ON THE SIMULATION
	list<int> cpy = path;
	while( !cpy.empty( ) )
	{
		int n = cpy.front( );
		cpy.pop_front( );
		sim.moveHead( nextMove( w, headNode, n ) );
		sim.updatePlayfield( );
		headNode = n;
	}

	// reset locals
	grid = sim.getGrid();
	tail = sim.getTail();
	head = sim.headPosition();
	food = sim.foodPosition();
	tailpt = tail.front();
	headNode = head.first * w + head.second;
	foodNode = food.first * w + food.second;
	tailNode = tailpt.first * w + tailpt.second;

	for( int k : { -w, 1, w, -1 } )
	{
		int tailS = tailNode + k;
		if( tailS >= 0 && tailS < G->V( ) )
			if( grid[tailS / w][tailS % w] == CLEAR_VALUE )
				tailNode = tailS;
	}
	// set the graph to have a clear value at the tail
	grid[tailNode / w][tailNode % w] = CLEAR_VALUE;

	G = new Graph( grid );

	heuristic = new Heuristic( sim.getGrid( ), G->Vertices( ) );

	// search to tail
	AStar findTail( G, headNode, tailNode, heuristic->get( ) );
	delete G;
	delete heuristic;

	// check push the path to the tail
	if( !findTail.hasPath( tailNode ) )
		trap = 1;
	pushPath( findTail.pathTo( tailNode ) );

	if( trap )
	{
		// reset locals & search to tail
		grid = pf->getGrid();
		tail = pf->getTail();
		head = pf->headPosition();
		food = pf->foodPosition();
		tailpt = tail.front();
		headNode = head.first * w + head.second;
		foodNode = food.first * w + food.second;
		tailNode = tailpt.first * w + tailpt.second;

		for( int k : { -w, 1, w, -1 } )
		{
			int tailS = tailNode + k;
			if( tailS >= 0 && tailS < G->V( ) )
				if( grid[tailS / w][tailS % w] == CLEAR_VALUE )
					tailNode = tailS;
		}
		// set the graph to have a clear value at the tail
		grid[tailNode / w][tailNode % w] = CLEAR_VALUE;

		G = new Graph( grid );

		heuristic = new Heuristic( pf->getGrid( ), G->Vertices( ) );

		AStar follow( G, headNode, tailNode, heuristic->get( ) );
		path = follow.pathTo( tailNode ); // reassign

		delete G;
		delete heuristic;
	}
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
