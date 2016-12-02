/*description of the different structurs*/
#ifndef STRUCT_H
#define STRUCT_H

#include <panel.h>


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

typedef struct _Path {//list of lab case and its size
	Lcase path;
	int size;
	
}Path;

typedef struct _Player {//player
	int lastX;//last position of the player
	int lastY;
	int X;//curent position of the player
	int Y;
	int turn;
	int energy;
	int mode;
	Path otherP;
	Path tresor;
	
}Player;

typedef struct _Map {//the labyrinth

	//WINDOW *win;// to use with ncurses
	char name[50];
	char infoP1[10][50];
	char infoP2[10][50];
	int width;
	int heigth;
	char **cases;
	Player* players[3];//[P1;P2;Tresor]
	
}Map;

typedef struct _WIN_struct {

	WINDOW *win;
	const char *label;
	const char *buttLab[7];
	int posButt[7][2];
	int numButt;
	
	
}WIN;



#endif
