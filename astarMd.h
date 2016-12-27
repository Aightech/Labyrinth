#ifndef ASTARMD_H
#define ASTARMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

int astarMode(Map *L);
Node *initOpenList(Map *L,int x, int y);
Node *newNode(Map *L,int x, int y,Node * neigh); //create a new case for a neighbour of c
int distNtoP(Map *L,int P,Node *N);
int distance_to_treasure(Map *L,int x,int y);
int abs(int x);


#endif
