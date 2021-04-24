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
        grid[head.first][head.second] = HEAD_VALUE;

        // move tail
        grid[ tail.front( ).first ][ tail.front( ).second ] = CLEAR_VALUE;
        tail.push( head );
        tail.pop( );

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
    int origHead = headNode;
    int foodNode = food.first * w + food.second;
    int tailNode = tailpt.first * w + tailpt.second;

    if( pf->getTail( ).size( ) <= 3 )
    {
        Graph *G = new Graph( grid );
        Heuristic heuristic( G->Vertices( ) );
        AStar findFood( G, headNode, foodNode, heuristic.get( ) );
        path = findFood.pathTo( foodNode );
        cout << "head " << headNode << " food " << foodNode << endl;
        delete G;
        return;
    }

    // set the graph to have a clear value here
    grid[tailpt.first][tailpt.second] = CLEAR_VALUE;
    Graph *G = new Graph( grid );

    Heuristic heuristic( G->Vertices( ) );

    // search to tail
    AStar headtotail( G, headNode, tailNode, heuristic.get( ) );

    // push the path to tail
    list<int> p = headtotail.pathTo( tailNode );
    pushPath( p );

    cout << "Head to tail" << endl;
    for( int x : p )
        cout << x << ' ';
    cout << endl;

    // Update Grid
    delete G;
    updateGrid( grid, pathtoPoint( w, p ), tail, head );
    G = new Graph( grid );

    headNode = head.first * w + head.second;

    // search to food
    AStar tailtofood( G, tailNode, foodNode, heuristic.get( ) );

    // push the path to food
    p = tailtofood.pathTo( foodNode );
    pushPath( p );

    cout << "tail to food" << endl;
    for( int x : p )
        cout << x << ' ';
    cout << endl;

    // Update Grid
    delete G;
    updateGrid( grid, pathtoPoint( w, p ), tail, head );
    grid[origHead / w][origHead % w] = CLEAR_VALUE;
    G = new Graph( grid );

    // search to original location
    AStar foodtohead( G, headNode, origHead, heuristic.get( ) );

    // push the path to the head
    pushPath( foodtohead.pathTo( headNode ) );

    cout << endl << endl;
    cout << "foodNode " << headNode << ' ' << grid[foodNode / w][foodNode % w] << endl;
    cout << "headNode " << origHead << ' ' << grid[headNode / w][headNode % w] << endl;
    cout << "food to head" << endl;
    for( int x : foodtohead.pathTo( headNode ) )
        cout << x << ' ';
    cout << endl << endl;
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
