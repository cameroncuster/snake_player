/********************************************************************//**
 * @file
 ***********************************************************************/
#include "simulation.h"

// Very simple wrapper class to play the game

Simulation::Simulation(RandomPlayer *p, Simulatefield *pf) : player(p), playfield(pf), gameOver(false), score(0) {}

// Clean up
Simulation::~Simulation()
{
   delete player;
   delete playfield;
}
// 1. Send the playfield to the player
// 2. Execute the move on the playfield
// 3. Check that the game hasn't ended
// 4. Update the playfield
ValidMove Simulation::makeMove()
{
   bool valid = false;

   ValidMove playerMove = player->makeMove(playfield);
   valid = playfield->moveHead(playerMove);

   if (!valid) gameIsOver();

   playfield->updatePlayfield();
   return playerMove;
}

void Simulation::gameIsOver() { gameOver = true; }

bool Simulation::isGameOver() const { return gameOver; }

int Simulation::getScore() const { return playfield->getScore() ; }

Simulatefield Simulation::field( ) const { return playfield; }
