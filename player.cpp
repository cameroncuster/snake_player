/********************************************************************//**
 * @file
 ***********************************************************************/
#include "player.h"
#include "genetic.h"

using namespace std;

Player::Player() { }

// construct a genetic algorithm to play x games
// the best player will be executed
// return the moves to execute if moves have been precalculated
ValidMove Player::makeMove(const Playfield *pf)
{
    Simulatefield *playfield = new Simulatefield( pf );
    if( moves.empty( ) )
    {
        Genetic snake( playfield );
        moves = snake.moves( );
    }
    ValidMove move = moves.front( );
    moves.pop( );
    return move;
}
