#ifndef ASTARMD_H
#define ASTARMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

int astarMode(Map *L);
Node *initOpenList(Map *L,int x, int y,char ** nds);

Node *newNode(Map *L,int x, int y,Node * neigh,char ** nds); //create a new Node(case) and return its adress.
Node * popList(Node * OpL,Node* clL);//remove the first node of the open list , and put on in the closed list.
Node * addNeigh(Map* L,Node* OpL,Node* from,char** nds);// try to create a node for each neighbor, and add them to the open list.
Node * extractPath(Node * clL);//start from the goal, iterativly,freing node that are not pathParent,taking pathParent node and put last node adress in its pathChild.

int rmList(Node* first);//free each node of the list

int distNtoP(Map *L,int P,Node *N);
int distance_to_treasure(Map *L,int x,int y);
int abs(int x);


#endif
