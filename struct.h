/*description of the different structurs*/
#ifndef STRUCT_H
#define STRUCT_H

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
	Path otherP;
	Path tresor;
	
}Player;

typedef struct _Map {//the labyrinth

	//WINDOW *win;// to use with ncurses
	int size[2];//width/heigth
	char **cases;
	Player* Players[3];//[P1;P2;Tresor]
	
}Map;

#endif
