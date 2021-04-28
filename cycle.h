/********************************************************************//**
 * @file
 ***********************************************************************/
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
	Cycle( const Playfield *, queue<pair<int, int>> );
	list<int> cycle( ) const;
private:
	void pushPath( const list<int> );
};
#endif
