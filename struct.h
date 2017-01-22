/*description of the different structurs*/
#ifndef STRUCT_H
#define STRUCT_H

#define nbrW 7
#include <panel.h>
#include <ncurses.h>

/*! \file struct.h
    \brief Data structures use in the program.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/


typedef struct _LStep{//case of lab to create path
	struct _LStep* from;
	struct _LStep* next;
	int nature;//a lab movement or a player movement
	int X;//position or row/line to move
	int Y;
	int lvlEnergy;//the curent level of enery at this step
	int cost;
	int heuristic;
}Lcase;

/**
 * \struct _Node
 * \brief Node is a case from the map.
 * It is used in Astar mode.
 */


typedef struct _Node{//the nodes
	int X,Y; /**< Position of the node in the map. */
	int cost; /**< Distance from the player to the current node */
	int heuristic; /**< Distance between the player and the treasure as the crows fly */
	char *ncase; /**< Pointer to a case of the map in order to get the data of */
	struct _Node * pathParent; /**< Pointer to get the Node evaluated before */
	struct _Node * pathChild; /**< Pointer to get the Node evaluated after */
	struct _Node * listNext; /**< Used if in Closedlist and Openlist */
	
}Node;

/**
 * \struct _Path
 * \brief List of lab node and its size.
 * It is used in Astar mode.
 */

typedef struct _Path {
	Node * first; /**< Pointer to the first node of the path */
	int size; /**< Number of cases in the Path */
	
}Path;

/**
 * \struct _Player
 * \brief Contains informations of position, energy and mode of a player.
 */

typedef struct _Player {
	int lastX; /**< Last X position of the player */
	int lastY;/**< Last Y position of the player */
	int X;/**< Current X position of the player  */
	int Y; /**< Current Y position of the player */
	int turn; /**< 1 if it is the turn of the player, 0 if it is the turn of the opponnent    */
	int energy; /**< Energy of the player, +1 every turn, -5 if the move is a rotation  */
	int mode; /**< Dumb, manual, random, A*, smart A*  */
	Path *toOtherP; /**< Path to go to the opponnent */
	Path *toGoal; /**< Path to go to the treasure */
	
}Player;

/**
 * \struct _Win
 * \brief 
 */

typedef struct _Win {

	WINDOW *win; /**<  */
	char label[50]; /**<  */
	char **labButt; /**<  */
	int **posButt; /**<  */
	int numButt; /**<  */
	
	
}Win;


/**
 * \struct _Map
 * \brief Contains informations of the Map.
 */

typedef struct _Map {//the labyrinth

	//WINDOW *win;// to use with ncurses
	char** listPlrName; /**<  */
	char** listSvrName; /**<  */
	char** listTimeOut; /**<  */
	char** listPrtName; /**<  */
	
	char PlayerName[25]; /**< Name of our player */
	char ServerName[50]; /**< Server data */
	int offline;
	char TimeOut[10]; /**< Max Time to Play */
	char PortName[10]; /**< Port Name */
	char name[50]; /**< Map Name */
	char infoP1[10][50]; /**< Info Player 1 */
	char infoP2[10][50]; /**< Info Player 2 */
	int width; /**< Width of the map */
	int heigth; /**< Heigth of the map */
	
	char comments[5][100]; /**<comments to send to the opponnent */
	
	char **cases; /**<  */
	Player* players[3];//[P1;P2;Tresor] /**< P1 is the opponnent, P2 is our player,  P3 is the treasure */
	
	PANEL  *panels[nbrW+1]; /**<  */
	Win **guiWins; /**<  */
	int mvC,mvL; /**<  */
	int turn; /**< Number of played turn */
	
}Map;





#endif
