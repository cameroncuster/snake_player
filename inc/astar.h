/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include <queue>
#include "graph.h"

/********************************************************************//**
 * @struct Node
 * 
 * Generic Node structure to support AStar client
 **********************************************************************/
struct Node
{
    int vertex;
    double overallDist;
    Node( int v, double o ) : vertex( v ), overallDist( o ) { }
};

/********************************************************************//**
 * @class nodeCompare
 * 
 * nodeComparison to build priority queue
 **********************************************************************/
class nodeCompare
{
    public:
        bool operator( ) ( const Node &lhs, const Node &rhs )
        {
            return ( lhs.overallDist < rhs.overallDist );
        }
};

/********************************************************************//**
 * @class AStar
 * 
 * Generic AStar client with modified heuristic
 **********************************************************************/
class AStar
{
    std::map<int, bool> marked;
    std::map<int, int> prev;
    std::map<int, int> dist;
    std::map<int, double> heuristic;
    std::priority_queue<Node, std::vector<Node>, nodeCompare> heap;
    int start, finish, columns;
    public:
    AStar( Graph *, int, int );
    AStar( Graph *, int, int, std::map<int, double> );

    bool hasPath( int );
    std::list<int> pathTo( int );
    private:
    void relax( int, int, Graph * );
    int straightLineDistance( int ) const;
};
#endif
