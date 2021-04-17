/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef GENETIC_H
#define GENETIC_H
#include "simulation.h"
#include "randomPlayer.h"

/********************************************************************//**
 * @class Genetic
 *
 * Genetic algorithm object to simulate x games and evaluate the best
 * player
 **********************************************************************/
class Genetic
{
    std::queue<ValidMove> optimalMoves;
    std::vector<Simulation *> games;
    public:
    Genetic( Playfield *pf );
    std::queue<ValidMove> moves( ) const;
    private:
    void evolve( );
};
#endif
