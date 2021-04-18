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
   ValidMove playerMove = player->makeMove(playfield);
   bool over = playfield->moveHead(playerMove);

   if (!over) gameIsOver();

   playfield->updatePlayfield();
   return playerMove;
}

void Simulation::gameIsOver() { gameOver = true; }

bool Simulation::isGameOver() const { return gameOver; }

int Simulation::getScore() const { return playfield->getScore() ; }
