/********************************************************************//**
 * @file
 ***********************************************************************/
#include "genetic.h"

using namespace std;

Genetic::Genetic( Simulatefield *pf )
{
    // malloc
    population.resize( POPULATION );
    ended.resize( POPULATION );

    // assign initial game state
    for( int i = 0; i < POPULATION; i++ )
    {
        RandomPlayer *p = new RandomPlayer( );
        Simulatefield *field = new Simulatefield( pf );
        Simulation *s = new Simulation( p, field );
        queue<ValidMove> q;
        population[i] = { s, q };
    }

    // generational development (e.a. evolution) -> GAs are a subset of evolutionary algorithms
    for( int g = 0; g < GENERATIONS; g++ )
    {
        // evolve the next generation of snakes
        evolve( );

        // find top 10 to populate next generation
        map<int, Organism> nextGen;
        for( Organism o : population )
            if( o.simulation->getScore( ) > nextGen.begin( )->first || nextGen.size( ) < 10 )
                nextGen[ o.simulation->getScore( ) ] = o;

        // assign the moves of the fittest organism
        map<int, Organism>::iterator it = nextGen.end( );
        it--;
        fittest = it->second;

        // extract the optimal organisms
        int i = 0;
        vector<Organism> fittest( NEXTGEN );
        for( pair<int, Organism> o : nextGen )
            fittest[i++] = o.second;

        // populate the next generation
        // i = 10
        for( auto &o : population )
            o = fittest[i % 10];
    }
}

queue<ValidMove> Genetic::moves( ) const
{
    return fittest.moves;
}

void Genetic::evolve( )
{
    int simulationCount = POPULATION;
    for( unsigned i = 0; i < MOVES && simulationCount > NEXTGEN; i++ )
        for( unsigned j = 0; j < POPULATION && simulationCount > NEXTGEN; j++ )
        {
            population[j].moves.push( population[j].simulation->makeMove( ) );
            if( population[j].simulation->isGameOver( ) )
                if( !ended[j] )
                {
                    ended[j] = 1;
                    simulationCount--;
                }
        }
}
