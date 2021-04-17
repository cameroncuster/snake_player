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
    Playfield *playfield = Playfield( pf )
    if( moves.emtpy( ) )
    {
        Genetic snake( playfield );
        moves = snake.moves( );
    }
    ValidMove move = moves.top( );
    moves.pop( );
    return move;
}
