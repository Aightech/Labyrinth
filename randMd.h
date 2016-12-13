#ifndef RANDMD_H
#define RANDMD_H
#include "struct.h"
#include "labyrinthAPI.h"

void gene_randmove(Map* L,t_move *move, int P);

int testMoveM(Map *L,int P);

void convert_movetype(int type, t_move *move);

void randMode(Map *L);

#endif
