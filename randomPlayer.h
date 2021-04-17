#ifndef __RANDOMPLAYER_H
#define __RANDOMPLAYER_H
#include <list>
#include <queue>
#include <map>
#include <limits>
#include <vector>
#include "playfield.h"
#include "simulation.h"

class RandomPlayer
{
    public:
    RandomPlayer ();
    ValidMove makeMove(Playfield *);
    private:
};
#endif
