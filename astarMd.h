#ifndef ASTARMD_H
#define ASTARMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

/*! \file astarMd.h
    \brief A* related functions.
    
    Details.
*/

/*! \fn int astarMode(Map *L);
    \brief Generate simple A* behavior.
    \param L The labyrinth map structur.
*/
/*! \fn Node *initOpenList(Map *L,int x, int y,char ** nds)
    \brief Initialise and return the node of the position (x,y).
    \param L The labyrinth map structur.
    \param x The x coordinate of the staring point.
    \param y The y coordinate of the staring point.
    \param nds The character array of 0/1 (making easier checking if cases have been checked.)
*/
/*! \fn Node *newNode(Map *L,int x, int y,Node * neigh,char ** nds); 
    \brief Initialise and return the node cominf from fromN.
    \param L The labyrinth map structur.
    \param x The x coordinate of the staring point.
    \param y The y coordinate of the staring point.
    \param nds The character array of 0/1 (making easier checking if cases have been checked.)
*/


int astarMode(Map *L);

Path * astarPath(Map* L, int P);
Node *initOpenList(Map *L,int x, int y,char ** nds);

Node *newNode(Map *L,int x, int y,Node * parent,char ** nds); //create a new Node(case) and return its adress.
Node * popList(Node * OpL);//remove the first node of the open list.
Node * addNeigh(Map* L,Node* OpL,char** nds);// try to create a node for each neighbor, and add them to the open list.
Node * extractPath(Node * clL);//start from the goal, iterativly,freing node that are not pathParent,taking pathParent node and put last node adress in its pathChild.
Node* addToList(Node *N1,Node* NtoAdd);//add a node to a list sort heuristicly increasing

int rmList(Node* first);//free each node of the list

int distNtoP(Map *L,int P,Node *N);
int distance_to_treasure(Map *L,int x,int y);
int abs(int x);


#endif
