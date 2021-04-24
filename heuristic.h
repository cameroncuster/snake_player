#ifndef HEURISTIC_H
#define HEURISITC_H
#include <vector>
#include <set>
#include <map>

using namespace std;

class Heuristic
{
    std::map<int, double> heuristic;
public:
    Heuristic( std::vector<std::vector<int>>, std::set<int> );

    std::map<int, double> get( ) const;
};
#endif
