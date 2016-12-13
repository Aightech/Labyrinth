#ifndef MANUALMD_H
#define MANUALMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

void gene_randmove(Map* L,t_move *move, Player *player);

int testMoveM(Player *player,t_move *move,int type);

void convert_movetype(int type, t_move *move);

void randMode(Map *L)

#endif
