/********************************************************************//**
 * @file
 ***********************************************************************/
#include "genetic.h"

using namespace std;

Genetic::Genetic( Simulatefield *pf )
{
    games.resize( FIRSTGEN );
    ended.resize( FIRSTGEN );
	for( int i = 0; i < FIRSTGEN; i++ )
    {
        RandomPlayer *p = new RandomPlayer( );
        Simulatefield *playfield = new Simulatefield( pf );
		games[i] = new Simulation( p, playfield );
    }
	// expand for multiple generations
    vector<queue<ValidMove>> movesinSimulation = evolve( );
	int optimalPlayer = 0;
	int maxScore = 0;
	for( unsigned i = 0; i < games.size( ); i++ )
        if( !ended[i] )
        {
            maxScore = max( maxScore, games[i]->getScore( ) );
            if( maxScore == games[i]->getScore( ) )
                optimalPlayer = i;
        }
	optimalMoves = movesinSimulation[ optimalPlayer ];
}

queue<ValidMove> Genetic::moves( ) const
{
    return optimalMoves;
}

vector<queue<ValidMove>> Genetic::evolve( )
{
	vector<queue<ValidMove>> movesinSimulation( FIRSTGEN );
	unsigned gamesOver = 0;
    for( unsigned i = 0; i < FIRSTGEN && gamesOver < games.size( ) - 2; i++ )
    {
		for( unsigned j = 0; j < games.size( ); j++ )
        {
            if( gamesOver >= games.size( ) - 2 )
                break;
            if( !games[j]->isGameOver( ) )
                movesinSimulation[j].push( games[j]->makeMove( ) );
            else if( !ended[j] )
            {
                ended[j] = 1;
                gamesOver++;
            }
        }
    }
	return movesinSimulation;
}
