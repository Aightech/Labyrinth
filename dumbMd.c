#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mapping.h"
#include "guilib.h"
#include "strlib.h"
#include "offline.h"

#include "labyrinthAPI.h"

/*! \file dumbMd.c
    \brief Dumb mode related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

void dumbMode(Map* L)
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
				ret = getMove(opMove);
				moveP(L,1,opMove);
			}
			else
			{
				getMoveOff(L,1,opMove);
				ret = movement(L,1,opMove);
			}
		}
		else
		{
			if(L->offline==0)
			{
				movement(L,0,myMove);
				sendComment(L->comments[rand()%5]);
				ret = sendMove(*myMove);
			}
			else
				ret =movement(L,0,myMove);

		}
		  //endwin();
		  //printLabyrinth();
		  dispInfo(L);
		dispMap(L);
		  
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
