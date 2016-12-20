#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include "labyrinthAPI.h"
#include "mapping.h"
#include <unistd.h>

void manualMode(Map* L)
{
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move* move=(t_move*) malloc(sizeof(t_move));
	move->type = DO_NOTHING;
	move->value = 0;
	t_move moveOp;
	int choice=40;
	
	
	while(ret==MOVE_OK)
	{
		
		if (L->players[0]->turn==1&&L->players[1]->mode!=1)//op turn	
		{
			addStr(L->infoP2[5],"                         ","");
			ret = getMove( &moveOp);
			movement(L,1,&moveOp);
		}
		else if (L->players[0]->turn==1&&L->players[1]->mode==1)	
		{
			
			choice=GUI(L,choice);
			switch(choice)
			{
			
				/*MANUAL MOVES*/
				case 40:
					moveOp.type=MOVE_LEFT;
				break;
				case 41:
					moveOp.type=MOVE_UP;
				break;
				case 42:
					moveOp.type=MOVE_DOWN;
				break;
				case 43:
					moveOp.type=MOVE_RIGHT;
				break;
				
			}
			//ret = getMove( &moveOp);
			moveP(L,1,&moveOp);
		}
		else
		  {
		  	addStr(L->infoP1[5],"                         ","");
		  	choice=GUI(L,choice);
			switch(choice)
			{
				
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
			}
			if(L->players[1]->mode!=1)
		    		ret = sendMove(*move);
		    
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
