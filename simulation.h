/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef SIMULATION_H
#define SIMULATION_H
#include <map>
#include "randomPlayer.h"

/********************************************************************//**
 * @class Simulation
 *
 * Simulation class which is really just a place to bring together the playfield
 * player, and their interaction to simulate games
 **********************************************************************/
class Simulation
{
   RandomPlayer *player;
   Playfield *playfield;
   bool gameOver;
   int  score;
public:
   Simulation(RandomPlayer *, Playfield *);
   ~Simulation();

   bool isGameOver() const;
   void gameIsOver();
   int getScore() const;
   bool makeMove();
};
#endif
