/********************************************************************//**
 * @file
 ***********************************************************************/
#include "game.h"

// Very simple wrapper class to play the game

Game::Game(Player *p, Playfield *pf) : player(p), playfield(pf), gameOver(false), score(0) {}

// Clean up
Game::~Game()
{
   delete player;
   delete playfield;
}

// 1. Send the playfield to the player
// 2. Execute the move on the playfield
// 3. Check that the game hasn't ended
// 4. Update the playfield
bool Game::makeMove()
{
   bool retVal = false;
   
   ValidMove playerMove = player->makeMove(playfield);
   retVal = playfield->moveHead(playerMove);

   if (!retVal) gameIsOver();

   playfield->updatePlayfield();
   return !isGameOver();
}

void Game::gameIsOver() { gameOver = true; }

bool Game::isGameOver() const { return gameOver; }

int Game::getScore() const { return playfield->getScore() ; }
