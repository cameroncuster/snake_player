/********************************************************************//**
 * @file
 ***********************************************************************/
#include "simulation.h"

extern ValidMove nextMove( int, int, int );

// execute the path to the food on the simulation
// uses pointer so acutal moves were excuted on the same field passed as param
Simulation::Simulation( Simulatefield *simulation, std::list<int> path )
{
    int headNode = simulation->headPosition( ).first *
        simulation->getGrid( )[0].size( ) +
        simulation->headPosition( ).second;

    while( !path.empty( ) )
    {
        int n = path.front( );
        path.pop_front( );
        simulation->moveHead( nextMove( simulation->getGrid( )[0].size( ), headNode, n ) );
        simulation->updatePlayfield( );
        headNode = n;
    }
}
