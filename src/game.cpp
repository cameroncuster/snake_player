/********************************************************************//**
 * @file
 ***********************************************************************/
#include "inc/game.h"

Game::Game(Player *p, Playfield *pf) : player(p), playfield(pf), gameOver(false), score(0) {}

Game::~Game()
{
   delete player;
   delete playfield;
}

bool Game::makeMove()
{
   static int lastScore = 0;
   static int ticksSinceLastScore = 0;
   static int tooManyTurns = (playfield->getGrid())[0].size() * playfield->getGrid().size() * 10;

   bool retVal = false;

   ValidMove playerMove = player->makeMove(playfield);
   retVal = playfield->moveHead(playerMove);

   if (!retVal || tooManyTurns < ticksSinceLastScore) gameIsOver();

   if (lastScore == playfield->getScore())
      ticksSinceLastScore++;
   else
   {
      ticksSinceLastScore = 0;
      lastScore = playfield->getScore();
   }

   playfield->updatePlayfield();
   return !isGameOver();
}

void Game::gameIsOver() { gameOver = true; }

bool Game::isGameOver() const { return gameOver; }

int Game::getScore() const { return playfield->getScore() ; }
