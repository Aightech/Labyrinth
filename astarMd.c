#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "Astar.h"
#include "labyrinthAPI.h"
#include <unistd.h>

Node newCase(Map *L, Node c, int x, int y) //create a new case for a neighbour of c
{
	Case v;
	v.x=x;
	v.y=y;
	v.cost=c.cost+1;
	v.heuristique=v.cost+distance_to_treasure(L,x,y);
	v.xp=c.x;
	v.yp=c.y;
	return v;
}

int distance_to_treasure(Map *L,x,y)
{
	int d;
	int xt=L->players[2]->X;
	int yt=L->players[2]->Y;
	
	if (abs(Xt-x)<L->width)
		d=abs(Xt-x);
	else	
		d=L->width-abs(Xt-x);
		
	if (abs(Yt-y)<L->heigth)
		return d=d+abs(Yt-y);
	else
		return d=d+L->heigth-abs(Yt-y);		
		
}

int abs(int x)
{
	if (x<0)
		return -x;
	else
		return x;
}

List * add_to_list(List* list, Case c) //add the case c into list
{
	while(list->next!=NULL)
	{
	}
	
}

Case* check_lowest(List *list) //return the case with the lowest heuristique in list
{
}

Case Astar_case(Map *L, //return the case the player has to go to



	


