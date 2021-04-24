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

	if( pf->getTail( ).size( ) <= 3 )
	{
		Graph *G = new Graph( grid );
		Heuristic heuristic( G->Vertices( ) );
		AStar findFood( G, headNode, foodNode, heuristic.get( ) );
		path = findFood.pathTo( foodNode );
		delete G;
		return;
	}

	Simulatefield sim( pf );

	Graph *G = new Graph( grid );

	Heuristic heuristic( G->Vertices( ) );

	AStar findFood( G, headNode, foodNode, heuristic.get( ) );

	// push the path to food
	pushPath( findFood.pathTo( foodNode ) );

	// EXECUTE THE PATH TO THE FOOD ON THE SIMULATION
	list<int> cpy = path;
	while( !cpy.empty( ) )
	{
		int n = cpy.front( );
		cpy.pop_front( );
		sim.moveHead( nextMove( w, headNode, n ) );
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

	// set the graph to have a clear value at the tail
	grid[tailpt.first][tailpt.second] = CLEAR_VALUE;

	delete G;
	G = new Graph( grid );

	// search to tail
	AStar findTail( G, headNode, tailNode, heuristic.get( ) );

	// push the path to the tail
	pushPath( findTail.pathTo( tailNode ) );

	delete G;
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
