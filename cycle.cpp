#include "cycle.h"
#include "graph.h"
#include "astar.h"

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
    int tailNode = tailpt.first * w + tailpt.second; // trying to search for node that is not in the graph

    Graph *G = new Graph( grid );

    // ***** SUBROUTINE build the heuristic
    map<int, double> heuristic;
    for( int v : G->Vertices( ) )
        heuristic[v] = 1;

    if( pf->getTail( ).size( ) <= 3 )
    {
        AStar findFood( G, headNode, foodNode, heuristic );
        path = findFood.pathTo( foodNode );
        cout << "food " << foodNode << " head " << headNode << endl;
        return;
    }

    path.clear( );

    // ***** SUBROUTINE Establish Master Cycle ( EMC )
    // ***** SUBROUTINE Establish Master Path ( EMP )

    grid[tailpt.first][tailpt.second] = CLEAR_VALUE; // handle snake of size < 3

    // search
    AStar headtotail( G, headNode, tailNode, heuristic );

    // EMP
    pushPath( headtotail.pathTo( tailNode ) );

    // DEBUG
    for( int n : path )
        cout << n << ' ';
    cout << endl;

    // Update Grid
    delete G;
    // construct a simulation, execute the moves, and set the new grid
    G = new Graph( grid );

    // search
    AStar tailtofood( G, tailNode, foodNode, heuristic );

    // EMP
    pushPath( tailtofood.pathTo( foodNode ) );

    // DEBUG
    for( int n : path )
        cout << n << ' ';
    cout << endl;

    // Update Grid
    delete G;
    updateGrid( grid, pathtoPoint( w, path ), tail, head );
    G = new Graph( grid );

    // search
    AStar foodtohead( G, foodNode, headNode, heuristic );

    // EMP
    pushPath( foodtohead.pathTo( headNode ) );

    delete G; // Memory Management


    // DEBUG
    for( int n : path )
        cout << n << ' ';
    cout << endl;
}

list<int> Cycle::cycle( ) const { return path; }

void Cycle::pushPath( const list<int> p ) { for( int n : p ) path.push_back( n ); }
