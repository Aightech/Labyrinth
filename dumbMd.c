#include <stdio.h>
#include <stdlib.h>
#include "guilib.h"
#include "strlib.h"
#include "labyrinthAPI.h"
#include "mapping.h"
#include <unistd.h>

/*! \file dumbMd.c
    \brief Dumb mode related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

void dumbMode(Map* L)
{
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move* move=(t_move*) malloc(sizeof(t_move));
	move->type = DO_NOTHING;
	move->value = 0;
	t_move moveOp;
	
	
	while(ret==MOVE_OK)
	{
		
		if (L->players[0]->turn==1)	
		{
			ret = getMove( &moveOp);
			moveP(L,1,&moveOp);
		}
		else
		  {
		  	moveP(L,0,move);
		  	sendComment(L->comments[rand()%5]);
		    	ret = sendMove(*move);
		    
		  }
		  //endwin();
		  //printLabyrinth();
		  dispInfo(L);
		dispMap(L);
		  
	}
	
	
	
	
	
	
	/* end the connection, because we are polite */
	closeConnection();
	
	
}
