/********************************************************************//** * @file
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
	while( moves.empty( ) )
	{
		Simulatefield *playfield = new Simulatefield( pf );
		Genetic snake( playfield );
		moves = snake.moves( );
        delete playfield;
	}
	ValidMove move = moves.front( );
	moves.pop( );
	return move;
}
