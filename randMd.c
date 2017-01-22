#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "struct.h"
#include "guilib.h"
#include "mapping.h"
#include "strlib.h"
#include "randMd.h"
#include "offline.h"

#include "labyrinthAPI.h"


/*! \file randMd.c
    \brief Rand mode related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

void randMode(Map *L)
//instructions of the random mode of the game
{
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	
	t_move* myMove=(t_move*) malloc(sizeof(t_move));
	if (myMove==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE);
	myMove->type = DO_NOTHING;
	myMove->value = 0;
	
	
	t_move* opMove=(t_move*) malloc(sizeof(t_move));
	if (opMove==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE);
	opMove->type = DO_NOTHING;
	opMove->value = 0;
	
	dispMap(L);
	
	
	while(ret==MOVE_OK)
	{
		if (L->players[0]->turn==1)
		{
			if(L->offline==0)
			{
				addStr(L->infoP2[5],"                         ","");
				ret = getMove(opMove);
				movement(L,1,opMove);
			}
			else
			{
				getMoveOff(L,1,opMove);
				ret = movement(L,1,opMove);
			}
			      
		}
		else
		{
			addStr(L->infoP1[5],"                         ","");
			gene_randmove(L,myMove,0);
			if(L->offline==0)
			{
				movement(L,0,myMove);
				sendComment(L->comments[rand()%5]);
				ret = sendMove(*myMove);
			}
			else
				ret =movement(L,0,myMove);
		}
		
		//int ch = getch();
		//endwin();
		//printLabyrinth();
		dispInfo(L);
		dispMap(L);
		dispPath(L);
		  
	}
	if ((L->players[0]->turn==1 && ret == MOVE_WIN) || (L->players[0]->turn==0 && ret == MOVE_LOSE))
	{
		addStr(L->infoP1[4],"                                  ","");
		addStr(L->infoP2[6]," YOU LOOSE","");
		addStr(L->infoP1[6]," YOU WIN","");
		addStr(L->cases[L->heigth/2],"   YOU WIN","");
	}
	else
	{
	 	addStr(L->infoP1[4],"                                  ","");
		addStr(L->infoP1[6]," YOU LOOSE","");
		addStr(L->infoP2[6]," YOU WIN","");
		addStr(L->cases[L->heigth/2],"   YOU LOOSE","");
	}
	
	if(L->offline==0&&L->players[1]->mode!=1)
		/* end the connection, because we are polite */
		closeConnection();
		
	free(myMove);
	free(opMove);
	
	
	
}


void gene_randmove(Map *L,t_move *move,int P)
{
	int type,t=-1;
	while(t==-1)
	{
		type=rand()%9;      
		if (type==0 || type==1)      //row line
		{
			convert_movetype(type,move);
			move->value=rand()%L->heigth;
			t=testMoveM(L,P);
		}
		else if (type==2 || type==3) //row column
		{
			convert_movetype(type,move);
			move->value=rand()%L->width;
			t=testMoveM(L,P);
		}    
		else  //basic move of the player
		{
			convert_movetype(type,move);       
			t=testMoveP(L,P,move);
		}
	}
}


void convert_movetype(int type, t_move *move)
//convert an int, for example generate by rand, to a t_move type
{
   switch (type)
    {
    case 0:
      move->type=ROTATE_LINE_LEFT;
      break;
    case 1:
      move->type= ROTATE_LINE_RIGHT;
      break;
    case 2:
      move->type=ROTATE_COLUMN_UP;
      break;
    case 3:
      move->type=ROTATE_COLUMN_DOWN;
      break;
    case 4:
      move->type=MOVE_LEFT;
      break;
    case 5:
      move->type=MOVE_RIGHT;
      break;
    case 6:
      move->type=MOVE_UP;
      break;
    case 7:
      move->type=MOVE_DOWN;
      break;
    case 8:
      move->type=DO_NOTHING;
      break;
    }
}
  


  



