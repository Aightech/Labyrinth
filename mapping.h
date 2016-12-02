#ifndef MAPPING_H
#define MAPPING_H
#include "struct.h"
#include "labyrinthAPI.h"

Map* initMap();
void getMap(Map *L);
void updateMap(Map *L);

int testMoveP(Map *L,int P,t_move* move);//return 1. If can't move return : -1(wall) -2(player) 
int moveP(Map *L, int P,t_move* move);//return 1. If can't move return : -1(wall) -2(player) 
int moveMap(Map *L,int row, int line);//return 1. If can't move return : -1(not enought energy)


void addStr(char * target,char * add1,char * add2);
char *intTostr(int nb);
#endif
