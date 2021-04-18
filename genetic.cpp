/********************************************************************//**
 * @file
 ***********************************************************************/
#include "genetic.h"

using namespace std;

Genetic::Genetic( Simulatefield *pf )
{
    RandomPlayer *p = new RandomPlayer( );
    games.resize( FIRSTGEN );
	for( int i = 0; i < FIRSTGEN; i++ )
		games[i] = new Simulation( p, pf );
    evolve( );
	delete p;
}

Genetic::~Genetic( )
{
	for( int i = 0; i < FIRSTGEN; i++ )
		delete games[i];
}

queue<ValidMove> Genetic::moves( ) const
{
    return optimalMoves;
}

void Genetic::evolve( )
{
	unsigned gamesOver = 0;
    vector<bool> ended( games.size( ) );
    for( unsigned i = 0; i < FIRSTGEN && gamesOver < games.size( ) - 2; i++ )
    {
		for( unsigned j = 0; j < games.size( ); j++ )
        {
            if( gamesOver > games.size( ) - 2 )
                break;
            if( !games[i]->isGameOver( ) )
                games[i]->makeMove( );
            else if( !ended[j] )
            {
                ended[j] = 1;
                gamesOver++;
            }
        }
    }
    // track the moves in the simulation and get those to interface here
}
