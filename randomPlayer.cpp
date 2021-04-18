/********************************************************************//**
 * @file
 ***********************************************************************/
#include <random>
#include <chrono>
#include "randomPlayer.h"

using namespace std;

RandomPlayer::RandomPlayer() { }

bool RandomPlayer::valid( ValidMove move ) const
{
	return 0;
}

ValidMove RandomPlayer::makeMove( Simulatefield *pf )
{
	srand( time( NULL ) );
	ValidMove move = NONE;
	/*
	   while( !valid( move ) )
	   {
	   int m = rand( ) % 4;
	   if( m == 0 ) move = UP;
	   if( m == 1 ) move = DOWN;
	   if( m == 2 ) move = RIGHT;
	   if( m == 3 ) move = LEFT;
	   }
	 */
	int m = rand( ) % 4;
	if( m == 0 ) move = UP;
	if( m == 1 ) move = DOWN;
	if( m == 2 ) move = RIGHT;
	if( m == 3 ) move = LEFT;
	return move;
}
