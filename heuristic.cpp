#include "heuristic.h"

using namespace std;

Heuristic::Heuristic( set<int> V )
{
    for( int v : V )
        heuristic[v] = 1;
}

map<int, double> Heuristic::get( ) const { return heuristic; }
