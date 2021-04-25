#include <iostream>
#include "defines.h"
#include "heuristic.h"

using namespace std;

extern bool inBounds( const int w, const int h, const int i, const int j );

Heuristic::Heuristic( vector<vector<int>> grid, set<int> V )
{
	int w = grid[0].size( );
	int h = grid.size( );
    for( int v : V )
        heuristic[v] = 1;

    for( unsigned i = 0; i < grid.size( ); i++ )
    {
        for( unsigned j = 0; j < grid[0].size( ); j++ )
        {
            if( grid[i][j] == TAIL_VALUE )
            {
                for( int k = -1; k <= 1; k++ )
                    for( int l = -1; l <= 1; l++ )
                    {
                        if( !k && !l ) continue;
                        if( inBounds( w, h, i + k, j + l ) )
                        {
                            int node = ( i + k ) * w + ( j + l );
                            heuristic[node] = 2;
                        }
                    }
            }
        }
    }
}

map<int, double> Heuristic::get( ) const { return heuristic; }
