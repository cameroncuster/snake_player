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
	// expand for multiple generations
    vector<queue<ValidMove>> movesinSimulation = evolve( );
	int optimalPlayer = 0;
	int maxScore = 0;
	for( unsigned i = 0; i < games.size( ); i++ )
	{
		maxScore = max( maxScore, games[i]->getScore( ) );
		if( maxScore == games[i]->getScore( ) )
			optimalPlayer = i;
	}
	optimalMoves = movesinSimulation[ optimalPlayer ];
	delete p;
}

queue<ValidMove> Genetic::moves( ) const
{
    return optimalMoves;
}

vector<queue<ValidMove>> Genetic::evolve( )
{
	vector<queue<ValidMove>> movesinSimulation( FIRSTGEN );
	unsigned gamesOver = 0;
    vector<bool> ended( games.size( ) );
    for( unsigned i = 0; i < FIRSTGEN && gamesOver < games.size( ) - 2; i++ )
    {
		for( unsigned j = 0; j < games.size( ); j++ )
        {
            if( gamesOver > games.size( ) - 2 )
                break;
            if( !games[i]->isGameOver( ) )
                movesinSimulation[i].push( games[i]->makeMove( ) );
            else if( !ended[j] )
            {
                ended[j] = 1;
                gamesOver++;
            }
        }
    }
	return movesinSimulation;
}
