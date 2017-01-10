#ifndef RANDMD_H
#define RANDMD_H
#include "struct.h"
#include "labyrinthAPI.h"

/*! \file randMd.h
    \brief Rand mode related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

/*! \fn void gene_randmove(Map* L,t_move *move, int P)
    \brief Generate random moves until it is possible for player P to do it (Map rotations and DO_NOTHING include).
    \param L The labyrinth map structure.
    \param move A pointer to recover the generated move.
    \param P Number of the player we generate a move for.
*/
void gene_randmove(Map* L,t_move *move, int P);

/*! \fn void convert_movetype(int type, t_move *move)
    \brief Generate a random move from an integer (Map rotations and DO_NOTHING include).
    \param L The labyrinth map structure.
    \param move A pointer to recover the generated move.
    \param P Number of the player we generate a move for.
*/
void convert_movetype(int type, t_move *move);

/*! \fn void randMode(Map *L)
    \brief Run the mode of the game where the player play with random moves (Map rotations and DO_NOTHING include).
    \param L The labyrinth map structure.
*/
void randMode(Map *L);

#endif
