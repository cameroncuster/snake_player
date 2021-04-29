/********************************************************************//**
 * @file
 ***********************************************************************/
#include <iostream>
#include "defines.h"
#include "heuristic.h"

extern bool inBounds( const int w, const int h, const int i, const int j );

// build a heuristic function h(n) - implemented to weight the tail of the snake
// heavily, ideally the snake will follow the tail for path finding
// which will reduce the possibility of trapping itself inside it's tail
// Reasoning: less room to trap itself = less squares to be trapped in
Heuristic::Heuristic( std::vector<std::vector<int>> grid, std::set<int> V )
{
    for( int v : V )
        heuristic[v] = 0;

    for( unsigned i = 0; i < grid.size( ); i++ )
        for( unsigned j = 0; j < grid[0].size( ); j++ )
            if( grid[i][j] == TAIL_VALUE )
                for( int k = -1; k <= 1; k++ )
                    for( int l = -1; l <= 1; l++ )
                    {
                        if( i == j ) continue;
                        if( inBounds( grid[0].size( ), grid.size( ), i + k, j + l ) )
                        {
                            int node = ( i + k ) * grid[0].size( ) + ( j + l );
                            heuristic[node] = 0;
                        }
                    }
}

std::map<int, double> Heuristic::get( ) const { return heuristic; }
