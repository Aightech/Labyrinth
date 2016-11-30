#ifndef GUI_H
#define GUI_H
#include "struct.h"

int GUI(Map *L,int lstGUIh);
void win_show(WIN *win);
void boxe(WIN *win, int starty, int startx,const char *string);
int choice(WIN *win,int lstCh);
int dispMap(Map *L,WIN* win);//Display the labyrinth
int dispInfo(Map *L,WIN* win);//Display the Player info

#endif
