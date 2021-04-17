/********************************************************************//**
 * @file
 ***********************************************************************/
#include "genetic.h"

using namespace std;

Genetic::Genetic( Playfield *pf )
{
    RandomPlayer *p = RandomPlayer( );
    games.resize( 1000, Simulation( p, pf ) );
    evolve( );
}

queue<ValidMove> Genetic::moves( ) const
{
    return optimalMoves;
}

void Genetic::evolve( )
{
    vector<bool> ended( games.size( ) );
    for( int i = 0; i < 1000 || gamesOver < games.size( ) - 2; i++ )
    {
        int j = 0;
        for( Simulation s : games )
        {
            if( gamesOver > games.size( ) - 2 )
                break;
            if( !s.isGameOver( ) )
                s.makeMove( );
            else if( !ended[j] )
            {
                ended[j] = 1;
                gamesOver++;
            }
            j++;
        }
    }
    // track the moves in the simulation and get those to interface here
}
