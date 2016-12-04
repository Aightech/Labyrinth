#include <stdio.h>
#include <stdlib.h>

#include "gui.h"
#include "struct.h"
#include "mapping.h"
#include "dumbMd.h"




Path Astar(Map *L,int P1, int P2); //return the shortest path beetween P1 and P2 
Path Astarpp(Map L,int P1, int P2); //return the shortest path beetween P1 and P2 taking the change of map into account, evaluatng the advantages with evaluate();

int crowFly(Map *L,int P1,int P2);//evaluate the distance beetween P1 and P2(of the map L) as the crows flies 
int evaluate(Map *L);//Return the






int main()
{
	Map *L=initMap();
	initGUI(L);
	t_move* move=(t_move*) malloc(sizeof(t_move));
	
	int choice=40;
	while(choice!=-1)
	{
		choice=GUI(L,choice);
		switch(choice)
		{
			case 30://connection to the server
				getMap(L);//switch of the value getmap return to lauched the game mode
				dumbMode(L);
			break;
			
			/*MANUAL MOVES*/
			case 40:
				move->type=MOVE_LEFT;
				moveP(L,0,move);
			break;
			case 41:
				move->type=MOVE_UP;
				moveP(L,0,move);
			break;
			case 42:
				move->type=MOVE_DOWN;
				moveP(L,0,move);
			break;
			case 43:
				move->type=MOVE_RIGHT;
				moveP(L,0,move);
			break;
			
			/*PLAYER MODES*/
			case 50://DO NOTHING
			case 51://MANUAL
			case 52://AUTO
				L->players[0]->mode=choice%10;
				choice+=10;
			break;
			
			/*OPONENT MODES*/
			case 60://DO NOTHING
			case 61://MANUAL
			case 62://AUTO
				L->players[1]->mode=choice%10;
				choice=30;
			break;
				
   
			
		}
	}

	return 0;
}



