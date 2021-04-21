/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include <queue>
#include "graph.h"

using namespace std;

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
    map<int, bool> marked;
    map<int, int> prev;
    map<int, int> dist;
    map<int, double> heuristic;
    priority_queue<Node, vector<Node>, nodeCompare> heap;
    int start, finish, columns;
    public:
    AStar( Graph *, int, int );

    bool hasPath( int );
    list<int> pathTo( int );
    private:
    void relax( int, int, Graph * );
    int straightLineDistance( int ) const;
};
#endif
