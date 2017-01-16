#include <stdio.h>
#include <stdlib.h>
#include "guilib.h"
#include "strlib.h"
#include "labyrinthAPI.h"
#include "mapping.h"
#include <unistd.h>

/*! \file manualMd.c
    \brief Manual mode related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

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
				case 46:
					moveOp.type=DO_NOTHING;
				break;
				case 44:
					choice=40;
					L->mvC=0;
					while(choice!=45)
					{
						dispMap(L);
						choice=GUI(L,choice);
						switch(choice)
						{
							/*COLUMN MOVES*/
							case 40:
								L->mvL=-1;
								if(L->mvC<0)
									L->mvC--;
								else
									L->mvC=L->width-1;
							break;
							case 43:
								L->mvL=-1;
								if(L->mvC+1>L->width-1)
									L->mvC++;
								else
									L->mvC=0;
							break;
							/*LINE MOVES*/
							case 41:
								L->mvC=-1;
								if(L->mvL>0)
									L->mvL--;
								else
									L->mvL=L->heigth-1;
							break;
							case 42:
								L->mvC=-1;
								if(L->mvL+1<L->heigth)
									L->mvL++;
								else
									L->mvL=0;
							break;
						}
					}
					choice=40;
					while(choice!=45)
					{
						dispMap(L);
						choice=GUI(L,choice);
						switch(choice)
						{
							/*ROTATIONS MOVES*/
							case 40:
								if(L->mvC!=-1)
								{
									move->type=ROTATE_LINE_LEFT;
									move->value=L->mvC;
									mvwaddch(L->guiWins[0]->win, 12-L->heigth/2+L->mvC+1, 18-L->width/2-1, '>');
								}
							break;
							case 43:
								if(L->mvC!=-1)
								{
									move->type=ROTATE_LINE_RIGHT;
									move->value=L->mvC;
								}
							break;
							case 41:
								if(L->mvL!=-1)
								{
									move->type=ROTATE_COLUMN_UP;
									move->value=L->mvL;
								}
							break;
							case 42:
								if(L->mvL!=-1)
								{
									move->type=ROTATE_COLUMN_DOWN;
									move->value=L->mvL;
								}
							break;
						}
					}
				break;		
				
			
				
			}
			//ret = getMove( &moveOp);
			moveP(L,1,&moveOp);
		}
		else
		  {
		  	addStr(L->infoP1[4],"                                 ","");
		  	addStr(L->infoP1[4],"It's your turn, select a move.","");
		  	choice=GUI(L,choice);
			switch(choice)
			{
				
				/*MANUAL MOVES*/
				case 40:
					move->type=MOVE_LEFT;
				break;
				case 41:
					move->type=MOVE_UP;
				break;
				case 42:
					move->type=MOVE_DOWN;
				break;
				case 43:
					move->type=MOVE_RIGHT;
				break;
				case 46:
					move->type=DO_NOTHING;
				break;
				case 44:
					L->mvC=0;
					while(choice!=45)
					{
						dispMap(L);
						addStr(L->infoP1[3]," Select OK to confirm the line","");
						addStr(L->infoP1[4]," or the column to move.","");
						dispInfo(L);
						
						choice=GUI(L,choice);
						switch(choice)
						{
							/*COLUMN MOVES*/
							case 40:
								L->mvL=-1;
								if(L->mvC>0)
									L->mvC--;
								else
									L->mvC=L->width-1;
							break;
							case 43:
								L->mvL=-1;
								if(L->mvC+1<L->width)
									L->mvC++;
								else
									L->mvC=0;
							break;
							/*LINE MOVES*/
							case 41:
								L->mvC=-1;
								if(L->mvL>0)
									L->mvL--;
								else
									L->mvL=L->heigth-1;
							break;
							case 42:
								L->mvC=-1;
								if(L->mvL+1<L->heigth)
									L->mvL++;
								else
									L->mvL=0;
							break;
						}
					}
					choice=40;
					addStr(L->infoP1[3],"                              ","");
					addStr(L->infoP1[4],"                              ","");
					int selected=0;
					while(choice!=45|| selected!=1)
					{
						dispMap(L);
						addStr(L->infoP1[3]," Select the direction of the rotation.","");
						addStr(L->infoP1[4]," Then select OK to confirm.","");
						dispInfo(L);
						choice=GUI(L,choice);
						switch(choice)
						{
							/*ROTATIONS MOVES*/
							case 40:
								if(L->mvL!=-1)
								{
									move->type=ROTATE_LINE_LEFT;
									move->value=L->mvL;
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18+L->width/2+3, "  ");
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18-L->width/2-2, "<<");
									selected=1;
								}
							break;
							case 43:
								if(L->mvL!=-1)
								{
									move->type=ROTATE_LINE_RIGHT;
									move->value=L->mvL;
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18-L->width/2-2, "  ");
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18+L->width/2+3, ">>");
									selected=1;
								}
							break;
							case 41:
								if(L->mvC!=-1)
								{
									move->type=ROTATE_COLUMN_UP;
									move->value=L->mvC;
									mvwprintw(L->guiWins[0]->win, 12+L->heigth/2+3, 18-L->width/2+L->mvC+1, " ");
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2-1, 18-L->width/2+L->mvC+1, "^");
									selected=1;
								}
							break;
							case 42:
								if(L->mvC!=-1)
								{
									move->type=ROTATE_COLUMN_DOWN;
									move->value=L->mvC;
									mvwprintw(L->guiWins[0]->win, 12-L->heigth/2-1, 18-L->width/2+L->mvC+1, " ");
									mvwprintw(L->guiWins[0]->win, 12+L->heigth/2+3, 18-L->width/2+L->mvC+1, "v");
									selected=1;
								}
							break;
						}
					}
					
					mvwprintw(L->guiWins[0]->win, 12+L->heigth/2+3, 18-L->width/2+L->mvC+1, " ");
					mvwprintw(L->guiWins[0]->win, 12-L->heigth/2-1, 18-L->width/2+L->mvC+1, " ");
					mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18-L->width/2-2, "  ");
					mvwprintw(L->guiWins[0]->win, 12-L->heigth/2+L->mvL+1, 18+L->width/2+3, "  ");
					L->mvL=-1;
					L->mvC=-1;
					addStr(L->infoP1[3],"                                      ","");
					addStr(L->infoP1[4],"                              ","");
					
				break;
			}
			movement(L,0,move);
			if(L->players[1]->mode!=1)
			{
				sendComment(L->comments[rand()%5]);
		    		ret = sendMove(*move);
	    		}
		    
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

	/* end the connection, because we are polite */
	closeConnection();
	
	
}
