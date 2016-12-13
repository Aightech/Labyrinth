#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "labyrinthAPI.h"
#include <unistd.h>

void gene_randmove(Map *L,t_move *move,Player *player)
// pointeur move, largeur et longueur du lab
// run until generate a possible move 
{
  int type=0;
  int t=-1;
  srand(time(NULL));
  while(t==-1)
    {
      type=rand()%9;      
      if (type==0 || type==1)      //row line
	{
	  convert_movetype(t,move);
	  move->value=rand()%L->width;
	  t=testMoveM(player,move);
	}
      else if (type==2 || type==3) //row column
	{
	  convert_movetype(t,move);
	  move->value=rand()%L->height;
	  t=testMoveM(player,move);
	}    
      else  //basic move of the player
	{
	  convert_movetype(t,move);       
	  t=testMoveP(L,move);
    }
}

int testMoveM(Player *player,t_move *move,int type)
//return 0 if "move", which may be a rotation of the map, is possible for player and -1 otherwise 
{
    if (player->energy<5)
    return -1;
  else
    {
      convert_movetype(type,move);
      return 0;
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
  

void MoveM(Map *L,t_move move)
//apply changes generate by move to the current map L
{
  int i;
  char temp;
  switch (move->type)
    {
    case ROTATE_LINE_LEFT;
    temp=L->cases[move->value][0];
    for (i=0;i<L->width-1;i++)
      {
	L->cases[move->value][i]=L->cases[move->value][i+1];
      }
    L->cases[move->value][width-1]=temp;
    break;
    
    case ROTATE_LINE_RIGHT;
    temp=L->cases[move->value][width-1];
    for (i=1;i<L->width;i++)
      {
        L->cases[move->value][width-i]=L->cases[move->value][width-1-i];
      }
    L->cases[move->value][0]=temp;
    break;
    
    case ROTATE_COLUMN_DOWN;
    temp=L->cases[heigth-1][move->value];
    for (i=1;i<L->heigth;i++)
      {
	L->cases[heigth-i][move->value]=L->cases[heigth-1-i][move->value];
      }
    L->cases[0][move->value]=temp;
    break;
    
    case ROTATE_COLUM_UP;
    temp=L->cases[0][move->value];
    for (i=0;i<L->heigth-1;i++)
      {
	L->cases[i][move->value]=L->cases[i+1][move->value];
      }
    L->cases[height-1][move->value]=temp;
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
	t_move moveOp;
	int choice;
	
	
	while(ret==MOVE_OK)
	{
		
		//if (L->players[0]->turn==1&&L->players[1]->mode!=1)	
		  if (L->players[0]->turn==1)
		{
			ret = getMove( move);
			moveP(L,1,move);
			L->players[0]->turn=0; //*
			L->players[1]->turn=1; //*
			L->players[0]->energy++; //* 
					      
		}
		else
		  {
		    gene_randmove(L,move,L->players[1]);
		    if (move->type==ROTATE_COLUMN_UP || move->type==ROTATE_COLUMN_DOWN || move->type==ROTATE_LINE_LEFT ||move->type==ROTATE_LINE_RIGHT)
		    moveM(L,move);
		    ret = sendMove(move);
		    L->players[1]->turn=0; //*
		    L->players[0]->turn=1; //*
		    L->players[1]->energy++; //*
		  }
		  //endwin();
		  //printLabyrinth();
		  dispInfo(L);
		dispMap(L);
		  
	}
	
	
	
	
	
	
	/* end the connection, because we are polite */
	closeConnection();
	
	
}


