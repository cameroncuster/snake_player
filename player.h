#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include <queue>
#include <map>
#include <limits>
#include "playfield.h"
#include "simulatefield.h"

class Player
{
    std::queue<ValidMove> moves;
public:
   Player ();
   ValidMove makeMove(const Playfield *);
private:
};
#endif
