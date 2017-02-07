#ifndef GUI_H
#define GUI_H
#include "struct.h"

/*! \file guilib.h
    \brief GUI related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

/*! \fn void initGUI(Map * L);
    \brief Allocate and initialize all the GUI structures.
    \param L The labyrinth map structure.
*/
void initGUI(Map * L);

void freeGUI(Map * L);

/*! \fn int GUI(Map * L,int lstGUIch);
    \brief  Allocate and initialize all the GUI structures.
    \param L The labyrinth map structure.
    \param lstGUIch last choice in the gui to make the active button to keep being activ after being push if there is no windows switch.
*/
int GUI(Map *L,int lstGUIch);

/*! \fn void showWin(Win *win);
    \brief  Monitor the gui system and all other graphical functions
    \param win The win to show.
    
*/
void showWin(Win *win);

/*! \fn void wboxe(Win *win, int starty, int startx,const char *string);
    \brief  draw a boxe at the position ( startx ; starty ) on the win given and write the string in it. (Rq: It size depend of the string size)
    \param win The win to show.
    \param starty The Y coordinate of the high-right corner of the boxe. 
    \param startx The X coordinate of the high-right corner of the boxe.
    \param string The string to write in the boxe.
*/
void wboxe(Win *win, int starty, int startx,const char *string);

/*! \fn int choice(Win *win,int lstCh);
    \brief  Enable to browse the different button of the win given, starting at the last choice given.
    \param win The win to browse.
    \param lstCh The index of the first button to activate.
*/
int choice(Win *win,int lstCh);

/*! \fn char * selectL(Map *L, int w, int starty, int startx, char ** list);
    \brief  Draw a menu where the different option 
    \param w The index of the window where the menu should be dispplayed 
    \param starty The Y coordinate of the high-right corner of the menu. 
    \param startx The X coordinate of the high-right corner of the menu. 
    \param list The list of the different item's label of the menu.
*/
char * selectL(Map *L, int w, int starty, int startx, char ** list);

/*! \fn int dispMap(Map *L);
    \brief  Display the labyrinth
    \param L The labyrinth map structure.
*/
int dispMap(Map *L);

int dispGraph(Map *L,Graph* G,Movement *M);

/*! \fn int eraseMap(Map *L);
    \brief  Erase the labyrynth
    \param L The labyrinth map structure.
*/
int eraseMap(Map *L);

/*! \fn int dispInfo(Map *L);
    \brief  Display the Player info
    \param L The labyrinth map structure.
*/
int dispInfo(Map *L);

/*! \fn int dispPath(Map* L);
    \brief  Display the path of players
    \param L The labyrinth map structure.
*/
int dispPath(Map* L);

int dispSeqMov(Map* L,Movement * M,int P);


#endif
