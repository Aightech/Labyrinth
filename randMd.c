#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "randMd.h"
#include "labyrinthAPI.h"
#include <unistd.h>
#include <time.h>

// pointeur move, largeur et longueur du lab
// run until generate a possible move 

void gene_randmove(Map *L,t_move *move,int P)
{
  int type,t=-1;
  srand(time(NULL));
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
  


  
void randMode(Map *L)
//instructions of the random mode of the game
{
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move* myMove=(t_move*) malloc(sizeof(t_move));
	t_move* adMove=(t_move*) malloc(sizeof(t_move));
	myMove->type = DO_NOTHING;
	myMove->value = 0;
	
	
	while(ret==MOVE_OK)
	{
		if (L->players[0]->turn==1)
		{
			addStr(L->infoP2[5],"                         ","");
			ret = getMove(adMove);
			movement(L,1,adMove);
			      
		}
		else
		{
			addStr(L->infoP1[5],"                         ","");
			gene_randmove(L,myMove,0);
			movement(L,0,myMove);
			ret = sendMove(*myMove);
		}
		//endwin();
		//printLabyrinth();
		dispInfo(L);
		dispMap(L);
		  
	}
	if ((L->players[0]->turn==1 && ret == MOVE_WIN) || (L->players[0]->turn==0 && ret == MOVE_LOSE))
	{
		addStr(L->infoP2[5]," YOU LOOSE","");
		addStr(L->infoP1[5]," YOU WIN","");
	}
	else
	{
		addStr(L->infoP1[5]," YOU LOOSE","");
		addStr(L->infoP2[5]," YOU WIN","");
	}
	
	/* end the connection, because we are polite */
	closeConnection();
	
	
}


