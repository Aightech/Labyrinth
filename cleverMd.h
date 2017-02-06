#ifndef CLEVERMD_H
#define CLEVERMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

/*! \file astarMd.h
    \brief A* related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/


/*! \fn int astarMode(Map *L);
    \brief Generate simple A* behavior.
    \param L The labyrinth map structure.
*/
int cleverMode(Map *L);

void cleverMv(Map* L, int P,t_move* move);

int Max(Map *L,int depth,Movement* mv,int P);

int Min(Map *L,int depth,Movement* m,int P);//return the best this move could lead to

void initChilds(Movement *mv);
Movement * addChild(Movement *mv,int i);

Movement *initMovement(Movement *parent,int P,int moveType,int x, int y);

int evaluate(Map *L,Movement *M,int P);

int distMtoG(Map *L,Movement *M,int P, int G);
int astarDistMtoG(Map *L,Movement *M,int P, int G);Node *newNodeC(Movement *M,int x, int y,Node * parent,char ** nds); //create a new case for a neighbour of c
Node * addNeighC(Movement *M,Node* opL,char** nds);// try to create a node for each neighbor, and add them to the open list.
int distNtoPC(Movement *M,int P,Node *N);


Movement *addToListMIN(Movement * M1,Movement * NtoAdd);
Movement *addToListMAX(Movement * M1,Movement * NtoAdd);




#endif
