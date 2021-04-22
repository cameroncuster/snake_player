#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include <queue>
#include <map>
#include <limits>
#include "playfield.h"

class Player
{
   std::list<int> path;
public:
   Player ();
   ValidMove makeMove(const Playfield *);
private:
   void pushPath(std::list<int>);
};
#endif
