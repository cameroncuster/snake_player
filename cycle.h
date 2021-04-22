#ifndef __CYCLE_H
#define __CYCLE_H
#include <list>
#include <queue>
#include "playfield.h"

using namespace std;

class Cycle
{
	list<int> path;
public:
	Cycle( const Playfield * );
	list<int> cycle( ) const;
private:
	void pushPath( const list<int> );
};
#endif
