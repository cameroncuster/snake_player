/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef GENETIC_H
#define GENETIC_H
#include "defineGen.h"
#include "simulation.h"

/********************************************************************//**
 * @class Genetic
 *
 * Genetic algorithm object to simulate x games and naturally select the best
 * players to populate the next generation
 **********************************************************************/
class Genetic
{
    std::queue<ValidMove> optimalMoves;
    std::vector<Simulation *> games;
    std::vector<bool> ended;
    public:
    Genetic( Simulatefield *pf );
    std::queue<ValidMove> moves( ) const;
    private:
	std::vector<std::queue<ValidMove>> evolve( );
};
#endif
