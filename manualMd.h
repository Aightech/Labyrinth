#ifndef MANUALMD_H
#define MANUALMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

/*! \file manualMd.h
    \brief Manual mode related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

/*! \fn void manualMode(Map* L)
    \brief Run the mode of the game where the player control his moves turn by turn with the console.
    \param L The labyrinth map structure.
*/
void manualMode(Map* L);

/*! \fn void manualMv(Map* L, int P,t_move* move);
    \brief Run the mode of the game where the player control his moves turn by turn with the console.
    \param L The labyrinth map structure.
    \param P The players to move.
    \param move The move that will be made.
*/
void manualMv(Map* L, int P,t_move* move);
#endif
