#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "guilib.h"
#include "struct.h"
#include "strlib.h"

#include "mapping.h"
#include "dumbMd.h"
#include "manualMd.h"
#include "randMd.h"
#include "astarMd.h"

/*! \file main.c
    \brief Main file to run the different modes and GUI options.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/



extern int debug;


int main()
{
	debug=0;
	time_t t;
	/* Intializes random number generator */
	srand((unsigned) time(&t));
	
	Map *L=initMap();
	initGUI(L);
	
	//t_move* move=(t_move*) malloc(sizeof(t_move));
	//printf("ROTATE_COLUMN_DOWN= %d ",ROTATE_COLUMN_DOWN);
	int choice=53,i;
	
	addStr(L->infoP1[5]," Select your mode.","");
	while(choice!=-1)
	{	
		dispInfo(L);
		choice=GUI(L,choice);
		switch(choice)
		{
			case 30:
				addStr(L->PlayerName,selectL(L,3,L->guiWins[3]->posButt[0][0],L->guiWins[3]->posButt[0][1]+8,L->listPlrName),"");
				choice++;
			break;
			case 31:
				addStr(L->ServerName,selectL(L,3,L->guiWins[3]->posButt[1][0],L->guiWins[3]->posButt[1][1]+8,L->listSvrName),"");
				choice++;
			break;
			case 32:
				addStr(L->TimeOut," timeout=",selectL(L,3,L->guiWins[3]->posButt[2][0],L->guiWins[3]->posButt[2][1]+9,L->listTimeOut));
				choice++;
			break;
			case 33:
				addStr(L->PortName,selectL(L,3,L->guiWins[3]->posButt[3][0],L->guiWins[3]->posButt[3][1]+7,L->listPrtName),"");
				choice++;
			break;
			case 34://connection to the server
				
				addStr(L->infoP1[5],"                                     ","");
				eraseMap(L);
				freeMap(L);
				getMap(L);//switch of the value getmap return to lauched the game mode
				if(L->players[1]->mode==1)
					/* end the connection, because we don't need the server anymore */
					closeConnection();
					
				if(L->players[0]->mode==0)//we are dumb
					dumbMode(L);
				else if(L->players[0]->mode==1)//we play manual
					manualMode(L);
				else if(L->players[0]->mode==2)//we play random
					randMode(L);
				else if(L->players[0]->mode==3)//we play astar
					astarMode(L);
			
				for(i=3;i<7;i++)
				{
					addStr(L->infoP1[i],"                                 ","");
					addStr(L->infoP2[i],"                                 ","");
				}
				addStr(L->infoP1[5]," Select your mode.","");
				
				choice=50;	
			break;
			case 35://connection to the server
				while(true){
					addStr(L->infoP1[5],"                                     ","");
					eraseMap(L);
					freeMap(L);
					getMap(L);//switch of the value getmap return to lauched the game mode
					if(L->players[1]->mode==1)
					/* end the connection, because we don't need the server anymore */
					closeConnection();
					
					if(L->players[0]->mode==0)//we are dumb
						dumbMode(L);
					else if(L->players[0]->mode==1)//we play manual
						manualMode(L);
					else if(L->players[0]->mode==2)//we play random
						randMode(L);
					else if(L->players[0]->mode==3)//we play astar
						astarMode(L);
					/*Pause l'application pour i milliseconds*/
					clock_t start,end;
					start=clock();
					int i=50;
		    			while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));
		    			
				}
				for(i=3;i<7;i++)
				{
					addStr(L->infoP1[i],"                                 ","");
					addStr(L->infoP2[i],"                                 ","");
				}
				addStr(L->infoP1[5]," Select your mode.","");
				choice=50;	
			break;
			
			/*MANUAL MOVES
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
			break;*/
			
			/*PLAYER MODES*/
			case 50://DO NOTHING
			case 51://MANUAL
			case 52://RANDOM
			case 53://ASTAR
				L->players[0]->mode=choice%10;
				addStr(L->infoP1[5]," Select the mode of your opponent.","");
				choice+=10;
			break;
			
			/*OPONENT MODES*/
			case 60://DO NOTHING
			case 61://MANUAL
			case 62://RANDOM MOVEP
			case 63://RANDOM MOVEP&M
			case 64://ASTAR
			case 65://Match
			case 66://CONTEST
				L->players[1]->mode=choice%10;
				addStr(L->infoP1[5]," Select <ENTER> to get a map","");
				choice=30;
			break;
				
   
			
		}
	}
	//freeMap(L);
	freeGUI(L);
	return 0;
}



