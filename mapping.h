#ifndef MAPPING_H
#define MAPPING_H
#include "struct.h"
#include "labyrinthAPI.h"

/*! \file mapping.h
    \brief Mapping related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
    
    Details.
*/

/*! \fn Map* initMap();
    \brief Return a map structure.
*/
Map* initMap();

/*! \fn void getMap(Map *L);
    \brief Connect to the server and get the labyrinth data.
    \param L The labyrinth map structur.
*/
void getMap(Map *L);

void updateMap(Map *L);

/*! \fn int testMoveP(Map *L,int P,t_move* move);
    \brief Return 1 if can't move return : -1(wall) -2(player)
    \param L The labyrinth map structure.
    \param P the player from which the movement will be made.
    \param move The movement that is tested.
*/
int testMoveP(Map *L,int P,t_move* move); 

/*! \fn int testMoveM(Map *L,int P)
    \brief Return 0 if player P has enough energy to move the Map and -1 otherwise 
    \param L The labyrinth map structure.
    \param P The player we want to know if he can move the map.
*/
int testMoveM(Map *L,int P);

/*! \fn int moveP(Map *L, int P,t_move* move);
    \brief Move the position of the player on the map. Return 1 if can't move return : -1(wall) -2(player)
    \param L The labyrinth map structure.
    \param P the player from which the movement will be made.
    \param move The movement that is tested.
*/
int moveP(Map *L, int P,t_move* move);

/*! \fn int moveM(Map *L,int P,t_move* move);
    \brief Rotate the map. Return 1 if can't move return : -1(not enought energy)
    \param L The labyrinth map structure.
    \param P the player from which the movement will be made.
    \param move The movement that is tested.
*/
int moveM(Map *L,int P,t_move* move);

/*! \fn int movement(Map *L,int P,t_move *move);
    \brief Rotate the map(moveM()) or move the player (moveP()). Return 1 if can't move return
    \param L The labyrinth map structure.
    \param P the player from which the movement will be made.
    \param move The movement that is tested.
*/
int movement(Map *L,int P,t_move *move);


int addStr(char * target,char * add1,char * add2);
char *intTostr(int nb);
int strToint(char *nbr);
#endif
