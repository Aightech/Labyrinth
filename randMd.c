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

int testMoveM(Map *L,int P)
//return 0 if "move", which may be a rotation of the map, is possible for player and -1 otherwise 
{
	if (L->players[P]->energy<5)
		return -1;
	else
		return 0;
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
	t_move* move=(t_move*) malloc(sizeof(t_move));
	move->type = DO_NOTHING;
	move->value = 0;
	
	
	while(ret==MOVE_OK)
	{
		
		//if (L->players[0]->turn==1&&L->players[1]->mode!=1)	
		if (L->players[0]->turn==1)
		{
			ret = getMove( move);
			if (move->type==ROTATE_COLUMN_UP || move->type==ROTATE_COLUMN_DOWN || move->type==ROTATE_LINE_LEFT ||move->type==ROTATE_LINE_RIGHT)
			moveM(L,1,move);
			else
			moveP(L,1,move);
			      
		}
		else
		{
			gene_randmove(L,move,0);
			if (move->type==ROTATE_COLUMN_UP || move->type==ROTATE_COLUMN_DOWN || move->type==ROTATE_LINE_LEFT ||move->type==ROTATE_LINE_RIGHT)
			{
				moveM(L,0,move);
				ret = sendMove(*move);
			}
			else
			{
				moveP(L,0,move);
				ret = sendMove(*move);
			}
		}
		endwin();
		printLabyrinth();
		//dispInfo(L);
		//dispMap(L);
		  
	}
	
	
	
	
	
	
	/* end the connection, because we are polite */
	closeConnection();
	
	
}


