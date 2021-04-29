#include <iostream>
#include <vector>
#include "defines.h"

// helper function to check bounds
bool inBounds( const int width, const int height, const int i, const int j )
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

// function to determine the next move given a position/point
ValidMove nextMove( int width, int source, int next )
{
    ValidMove move = NONE;
    const int delta[4] = { -width, 1, width, -1 };
    for( int i = 0; i < 4; i++ )
        if( source + delta[i] == next )
        {
            if( i == 0 ) move = UP;
            if( i == 1 ) move = RIGHT;
            if( i == 2 ) move = DOWN;
            if( i == 3 ) move = LEFT;
        }
    return move;
}
