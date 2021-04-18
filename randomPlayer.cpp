/********************************************************************//**
 * @file
 ***********************************************************************/
#include <chrono>
#include <random>
#include <algorithm>
#include "randomPlayer.h"

using namespace std;

RandomPlayer::RandomPlayer() { }

ValidMove RandomPlayer::makeMove( Simulatefield *pf )
{
	ValidMove move = NONE;
	vector<ValidMove> randomMoves = { UP, DOWN, LEFT, RIGHT };
	shuffle( randomMoves.begin( ), randomMoves.end( ), default_random_engine( chrono::system_clock::now().time_since_epoch().count() ) );
	randomMoves.push_back( NONE );
	bool valid = 0;
	for( unsigned i = 0; i < randomMoves.size( ) && !valid; i++ )
	{
		move = randomMoves[i];
		Simulatefield *copyfield = new Simulatefield( pf );
		valid = copyfield->moveHead( move );
        delete copyfield;
	}
	return move;
}
