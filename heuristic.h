/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef HEURISTIC_H
#define HEURISITC_H
#include <vector>
#include <set>
#include <map>

/********************************************************************//**
 * @class Heuristic
 *
 * Models a heuristic for an AStar search given the grid and a set of
 * vertices.
 * Object interface allows retreival of the heuristic.
 **********************************************************************/
class Heuristic
{
    std::map<int, double> heuristic;
    public:
    Heuristic( std::vector<std::vector<int>>, std::set<int> );

    std::map<int, double> get( ) const;
};
#endif
