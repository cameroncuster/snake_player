/********************************************************************//**
 * @file
 ***********************************************************************/
#include "../inc/simulation.h"

extern ValidMove nextMove( int, int, int );

// execute the path to the food on the simulation
// uses pointer so acutal moves were excuted on the same field passed as param
Simulation::Simulation( Simulatefield *simulation, std::list<int> path )
{
    int width = simulation->getGrid( )[0].size( );
    int headNode = simulation->headPosition( ).first * width +
        simulation->headPosition( ).second;

    // execute all moves in the path
    while( !path.empty( ) )
    {
        int next = path.front( );
        path.pop_front( );
        simulation->moveHead( nextMove( width, headNode, next ) );
        simulation->updatePlayfield( );
        headNode = next;
    }
}
