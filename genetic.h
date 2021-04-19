/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef GENETIC_H
#define GENETIC_H
#include "defineGEN.h"
#include "simulation.h"

/********************************************************************//**
 * @class Genetic
 *
 * Genetic algorithm object to simulate x games and naturally select the best
 * players to populate the next generation
 **********************************************************************/
class Genetic
{
    // c++ structure to associate a Game( playfield and player ) with the moves
    struct Organism
    {
        Simulation * simulation;
        std::queue<ValidMove> moves;
    };
    std::vector<Organism> population;
    std::vector<bool> ended;
    Organism fittest;
    public:
    Genetic( Simulatefield *pf );
    std::queue<ValidMove> moves( ) const;
    private:
    void evolve( );
};
#endif
