/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "astar.h"

using namespace std;

Player::Player() { }

bool inBounds( const int w, const int h, const int i, const int j )
{
    return i >= 0 && i < h && j >= 0 && j < w;
}

ValidMove Player::makeMove(const Playfield *pf)
{
    vector<std::vector<int>> grid = pf->getGrid();
    int w = grid[0].size( );
    int h = grid.size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;

	if( !path.empty( ) )
	{
	}

    Graph *G = new Graph( grid );

    // build the heuristic
    map<int, double> heuristic;
    for( int v : G->Vertices( ) )
        heuristic[v] = 1;

    // AStar head to tail
    AStar headtotail( G, headNode, tailNode, heuristic );

	// AStar tail to food
    AStar tailtofood( G, tailNode, foodNode, heuristic );

	// AStar food to tail
    AStar foodtotail( G, foodNode, newtailNode, heuristic );

    // check if a path exists - scan otherwise
    if( !astar.hasPath( foodNode ) )
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

    // find the optimal move w/o caching
    list<int> path = astar.pathTo( foodNode );
    if( !path.empty( ) ) path.pop_front( ); // remove the source

    // determine the move to make
    ValidMove move = NONE;
    const int delta[4] = { -w, 1, w, -1 };
    for( int i = 0; i < 4; i++ )
        if( headNode + delta[i] == path.front( ) )
        {
            if( i == 0 ) move = UP;
            if( i == 1 ) move = RIGHT;
            if( i == 2 ) move = DOWN;
            if( i == 3 ) move = LEFT;
        }

    delete G; // memory clean-up
    return move;
}
