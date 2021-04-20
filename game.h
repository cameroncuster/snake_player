/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef GAME_H
#define GAME_H
#include <map>
#include "player.h"

/********************************************************************//**
 * @class Game
 *
 * Game class which is really just a place to bring together the playfield
 * player, and their interaction
 **********************************************************************/
class Game
{
   Player *player;
   Playfield *playfield;
   bool gameOver;
   int  score;
public:
   Game(Player *, Playfield *);
   ~Game();

   bool isGameOver() const;
   void gameIsOver();
   int getScore() const;
   bool makeMove();
};
#endif
