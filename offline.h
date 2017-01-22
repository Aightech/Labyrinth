#ifndef OFFLINE_H
#define OFFLINE_H
#include "struct.h"
//#include "labyrinthAPI.h"

/*! \file offline.h
    \brief offline related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/


/*! \fn int sendMoveOff(Map* L, t_move* move);
    \brief Generate the shortest path to the goal with an A* algo.
    \param L The labyrinth map structure.
    \param P the player from which the path wll start.
    \param move the to do.
*/
int getMoveOff(Map* L,int P,t_move* move);

/*! \fn void astarMv(Map* L, int P,t_move* move);
    \brief Generate the shortest path to the goal with an A* algo.
    \param L The labyrinth map structure.
    \param P the player from which the path wll start.
    \param move the that has to be done.
*/
int sendMoveOff(Map* L,int P, t_move* move);





#endif
