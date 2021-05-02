/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef SIMULATION_H
#define SIMULATION_H
#include "simulatefield.h"

/********************************************************************//**
 * @class Simulation
 *
 * Simulate execution of the path on the given playfield.
 **********************************************************************/
class Simulation
{
    public:
        Simulation( Simulatefield *, std::list<int> );
};
#endif
