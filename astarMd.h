#ifndef ASTARMD_H
#define ASTARMD_H
#include "struct.h"
//#include "labyrinthAPI.h"

/*! \file astarMd.h
    \brief A* related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
    
    Details.
*/


/*! \fn int astarMode(Map *L);
    \brief Generate simple A* behavior.
    \param L The labyrinth map structure.
*/
int astarMode(Map *L);

/*! \fn Path * astarPath(Map *L,int P);
    \brief Generate the shortest path to the goal with an A* algo.
    \param L The labyrinth map structure.
    \param P the player from which the path wll start.
*/
Path * astarPath(Map* L, int P);

/*! \fn Node *initOpenList(Map *L,int x, int y,char ** nds)
    \brief Initialise and return the node of the position (x,y).
    \param L The labyrinth map structure.
    \param x The x coordinate of the staring point.
    \param y The y coordinate of the staring point.
    \param nds The character array of 0/1 (making easier checking if cases have been checked.)
*/
Node *initOpenList(Map *L,int x, int y,char ** nds);

/*! \fn Node *newNode(Map *L,int x, int y,Node * neigh,char ** nds); 
    \brief Initialise and return the node cominf from fromN.
    \param L The labyrinth map structure.
    \param x The x coordinate of the staring point.
    \param y The y coordinate of the staring point.
    \param nds The character array of 0/1 (making easier checking if cases have been checked.)
*/
Node *newNode(Map *L,int x, int y,Node * parent,char ** nds);

/*! \fn Node * addNeigh(Map* L,Node* OpL,char** nds);
    \brief try to create a node for each neighbor, and add them to the open list.
    \param L The labyrinth map structure.
    \param OpL The open list.
    \param nds The character array of 0/1 (making easier checking if cases have been checked.)
*/
Node * addNeigh(Map* L,Node* OpL,char** nds);

/*! \fn Node * extractPath(Node * clL);
    \brief Starting from the goal, iterativly,freing node that are not pathParent,taking pathParent node and put last node adress in its pathChild.
    \param clL closed list The open list.
*/
Node * extractPath(Node * clL);

/*! \fn Node* addToList(Node *N1,Node* NtoAdd);
    \brief Add a node to a list sort heuristicly increasing
    \param N1 First node of the the list to add.
    \param NtoAdd node to add to the list.
*/
Node* addToList(Node* N1,Node* NtoAdd);

/*! \fn int rmList(Node* first);
    \brief Free each node of the list
    \param first First of the the list to remove.
*/
int rmList(Node* first);

/*! \fn int distNtoP(Map *L,int P,Node *N)
    \brief Calculate the distance as the crows fly from the node N to the player P.
    \param L The labyrinth map structure.
    \param P Number of the Player.
    \param N Pointer to the Node.
*/
int distNtoP(Map *L,int P,Node *N);


#endif
