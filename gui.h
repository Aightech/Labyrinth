#ifndef GUI_H
#define GUI_H
#include "struct.h"
void initGUI(Map * L);
int GUI(Map *L,int lstGUIh);
//void win_show(WIN *win);
void showWin(Win *win);
//void boxe(WIN *win, int starty, int startx,const char *string);
void wboxe(Win *win, int starty, int startx,const char *string);
int choice(Win *win,int lstCh);
char * selectL(Map *L, int w, int starty, int startx, char ** list,int sizeL);

int dispMap(Map *L);//Display the labyrinth
int eraseMap(Map *L);//Erase the labyrynth
int dispInfo(Map *L);//Display the Player info
int dispPath(Map* L);//Display the path of players


#endif
