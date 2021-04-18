/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef SIMULATION_H
#define SIMULATION_H
#include <map>
#include "simulatefield.h"
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
   Simulatefield *playfield;
   bool gameOver;
   int  score;
public:
   Simulation(RandomPlayer *, Simulatefield *);
   ~Simulation();

   bool isGameOver() const;
   void gameIsOver();
   int getScore() const;
   bool makeMove();
};
#endif
