/********************************************************************//**
 * @file
 ***********************************************************************/
#include <utility>
#include "player.h"
#include "astar.h"

// DEBUG
#include <iostream>

using namespace std;

Player::Player() { }

ValidMove Player::makeMove(const Playfield *pf)
{
    vector<std::vector<int>> grid = pf->getGrid();
    int w = grid.size( );
    pair<int, int> head = pf->headPosition();
    pair<int, int> food = pf->foodPosition();
    int headNode = head.first * w + head.second;
    int foodNode = food.first * w + food.second;

    Graph *G = new Graph( grid );
    AStar astar( G, headNode, foodNode );

    while( !astar.hasPath( foodNode ) )
        break; // start scanning

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
