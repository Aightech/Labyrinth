#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "labyrinthAPI.h"
#include <unistd.h>

void move_alea(Map *L,t_move *move) // pointeur move, largeur et longueur du lab
{
  int t=-1;
  srand(time(NULL));
  while(t==-1)
    {
      move->type=rand()%9;
      if (move->type==0 || move->type==1) //rotate line
	move->value=rand()%L->width;
	t=testMoveM(L,move);
      else if (move->type==2 || move->type==3) //rotate column
	move->value=rand()%L->height;
t=testMoveM(L,move);
    }
}



