/********************************************************************//**
 * @file
 ***********************************************************************/
#include "cycle.h"
#include "graph.h"
#include "astar.h"
#include "heuristic.h"
#include "simulation.h"
#include "simulatefield.h"

using namespace std;

extern bool inBounds( const int, const int, const int, const int );
extern ValidMove nextMove( int, int, int );

static const vector<vector<int>> delta = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

Cycle::Cycle( const Playfield *pf, queue<pair<int, int>> tail )
{
    queue<pair<int, int>> tcpy = tail;
	vector<vector<int>> grid = pf->getGrid();
	int w = grid[0].size( );
	int h = grid.size( );
	pair<int, int> head = pf->headPosition();
	pair<int, int> food = pf->foodPosition();
	pair<int, int> tailpt = tail.front();
	int headNode = head.first * w + head.second;
	int foodNode = food.first * w + food.second;
	int tailNode = tailpt.first * w + tailpt.second;
	bool trap = 0;

	if( tail.size( ) <= 3 )
	{
		Graph *G = new Graph( grid );
		Heuristic heuristic( pf->getGrid( ), G->Vertices( ) );
		AStar findFood( G, headNode, foodNode, heuristic.get( ) );
		path = findFood.pathTo( foodNode );
		delete G;
		return;
	}

	Simulatefield sim( pf, tail );

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
    Simulatefield *sf = new Simulatefield( sim );
    Simulation simulateMoves( sf, path );
    /*
	list<int> cpy = path;
	while( !cpy.empty( ) )
	{
		int n = cpy.front( );
		cpy.pop_front( );
		sim.moveHead( nextMove( w, headNode, n ) );
		sim.updatePlayfield( );
		headNode = n;
	}
    */

	// reset locals
	grid = sf->getGrid();
	tail = sf->getTail();
	head = sf->headPosition();
	food = sf->foodPosition();
	tailpt = tail.front();
	headNode = head.first * w + head.second;
	foodNode = food.first * w + food.second;
	tailNode = tailpt.first * w + tailpt.second;
    delete sf;

	list<int> prevpath = path;

	for( int i = 0; i < 4; i++ )
	{
		pair<int, int> tailS = { tailpt.first + delta[i][0], tailpt.second + delta[i][1] };
		if( inBounds( w, h, tailS.first, tailS.second ) )
			if( grid[tailS.first][tailS.second] == CLEAR_VALUE )
			{
				tailNode = tailS.first * w + tailS.second;

				G = new Graph( grid );

				heuristic = new Heuristic( sim.getGrid( ), G->Vertices( ) );

				// search to tail
				AStar findTail( G, headNode, tailNode, heuristic->get( ) );
				delete G;
				delete heuristic;

				if( findTail.hasPath( tailNode ) )
				{
					pushPath( findTail.pathTo( tailNode ) );
					break;
				}
			}
	}

	// check push the path to the tail
	if( path == prevpath )
		trap = 1;

	if( trap )
	{
		// reset locals & search to tail
		grid = pf->getGrid();
		tail = tcpy;
		head = pf->headPosition();
		food = pf->foodPosition();
		tailpt = tail.front();
		headNode = head.first * w + head.second;
		foodNode = food.first * w + food.second;
		tailNode = tailpt.first * w + tailpt.second;

		for( int i = 0; i < 4; i++ )
		{
			pair<int, int> tailS = { tailpt.first + delta[i][0], tailpt.second + delta[i][1] };
			if( inBounds( w, h, tailS.first, tailS.second ) )
				if( grid[tailS.first][tailS.second] == CLEAR_VALUE )
				{
					tailNode = tailS.first * w + tailS.second;

					G = new Graph( grid );

					heuristic = new Heuristic( pf->getGrid( ), G->Vertices( ) );

					AStar follow( G, headNode, tailNode, heuristic->get( ) );

					delete G;
					delete heuristic;

					if( follow.hasPath( tailNode ) )
					{
						path = follow.pathTo( tailNode ); // reassign
						break;
					}
				}
		}
	}
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
