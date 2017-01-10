#include <stdio.h>
#include <stdlib.h>

#include "gui.h"
#include "struct.h"
#include "mapping.h"
#include "labyrinthAPI.h"
#include <unistd.h>



Map* initMap()
{
	Map* L=(Map *) malloc(sizeof(Map));
	L->width=21;
	L->heigth=12;
	L->mvC=-1;
	L->mvL=-1;
	L->cases=(char **) malloc(L->heigth*sizeof(char*));
	
	char MapI[]="---------------------  Project Labyrinth       2016/2017       ---------------------       ROB 3         ---------------------   ARLANDIS Maeva                           DEVILLARD  Alexis                          AUSSAGE Antoine   ---------------------";
	
	int i,j;
	for(i=0;i<L->heigth;i++)
	{
		L->cases[i]=(char*)malloc(L->width*sizeof(char));
		for(j=0;j<L->width;j++)
		{
			L->cases[i][j]=MapI[i*L->width+j];
		}
	}
	
	L->listPlrName=(char **) malloc(4*sizeof(char*));
	L->listPlrName[0]=(char*)malloc(25*sizeof(char));
	addStr(L->listPlrName[0],"aightech","");
	L->listPlrName[1]=(char*)malloc(25*sizeof(char));
	addStr(L->listPlrName[1],"BarbeBleue","");
	L->listPlrName[2]=(char*)malloc(25*sizeof(char));
	addStr(L->listPlrName[2],"K2SO","");
	L->listPlrName[3]=(char*)malloc(25*sizeof(char));
	addStr(L->listPlrName[3],"Darkradox","");
	
	
	addStr(L->PlayerName,L->listPlrName[0],"");//default;
	
	L->listSvrName=(char **) malloc(2*sizeof(char*));
	L->listSvrName[1]=(char*)malloc(50*sizeof(char));
	addStr(L->listSvrName[1],"pc4023.polytech.upmc.fr","");
	L->listSvrName[0]=(char*)malloc(50*sizeof(char));
	addStr(L->listSvrName[0],"pc4001.polytech.upmc.fr","");
	
	
	addStr(L->PlayerName,L->listSvrName[0],"");//default;
	
	L->listTimeOut=(char **) malloc(3*sizeof(char*));
	L->listTimeOut[0]=(char*)malloc(10*sizeof(char));
	addStr(L->listTimeOut[0],"100","");
	L->listTimeOut[1]=(char*)malloc(10*sizeof(char));
	addStr(L->listTimeOut[1],"10","");
	L->listTimeOut[2]=(char*)malloc(10*sizeof(char));
	addStr(L->listTimeOut[2],"1000","");
	
	addStr(L->TimeOut,L->listTimeOut[0],"");//default;
	
	L->listPrtName=(char **) malloc(1*sizeof(char*));
	L->listPrtName[0]=(char*)malloc(10*sizeof(char));
	addStr(L->listPrtName[0],"1234","");
	
	addStr(L->PortName,L->listPrtName[0],"");//default;
	
	
	
	
	addStr(L->infoP1[0],"  Aightech","");
	addStr(L->infoP1[1],"  0","");
	for(i=2;i<10;i++)
	{
		addStr(L->infoP1[i],"                   ","");
		addStr(L->infoP2[i],"                   ","");
	}
	addStr(L->infoP2[0],"  UNKNOWN","");
	addStr(L->infoP2[1],"  0","");
	
	for(i=0;i<3;i++)
	{
		L->players[i]=(Player*) malloc(sizeof(Player));
		L->players[i]->X=0;
		L->players[i]->Y=0;
		L->players[i]->mode=0;
		L->players[i]->toGoal=NULL;
	}
	return L;
	
}

void getMap(Map *L)
{
	
	char* labData;						/* data of the labyrinth */
	/* connection to the server */
	connectToServer( L->ServerName,strToint(L->PortName),L->PlayerName);
	int i,j;
	for(i=0;i<L->heigth;i++)//delete the last cases
	{
		free(L->cases[i]);
	}
	free(L->cases);
	eraseMap(L);
	
	
	switch(L->players[0]->mode)
	{
		case 0:
			addStr(L->infoP1[0],L->PlayerName,"  (DUMB)");
		break;
		case 1:
			addStr(L->infoP1[0],L->PlayerName,"  (MANUAL)");
		break;
		case 2:
			addStr(L->infoP1[0],L->PlayerName,"  (RANDOM)");
		break;
		case 3:
			addStr(L->infoP1[0],L->PlayerName,"  ( A* )");
		break;
	}
	
	char argMap[100];
	switch(L->players[1]->mode)
	{
		case 0:
			addStr(argMap,"DO_NOTHING",L->TimeOut);
			addStr(L->infoP2[0],"  DUMB","  (DO_NOTHING)");
		break;
		case 1:
			addStr(argMap,"PLAY_RANDOM",L->TimeOut);
			addStr(L->infoP2[0],"  MANUAL","  (MANUAL)");
		break;
		case 2:
			addStr(argMap,"PLAY_RANDOM rotation=False",L->TimeOut);
			addStr(L->infoP2[0],"  RANDOM MOVE PLAYER","  (RANDOM)");
		break;
		case 3:
			addStr(argMap,"PLAY_RANDOM",L->TimeOut);
			addStr(L->infoP2[0],"  RANDOM","  (RANDOM)");
		break;
		case 4:
			addStr(argMap,"ASTAR",L->TimeOut);
			addStr(L->infoP2[0],"  Clever","  ( A* )");
		break;
		case 5:
			addStr(argMap,"","");
			addStr(L->infoP2[0],"  Clever","  ( A* )");
		break;
		
	}
	dispInfo(L);
	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( argMap, L->name, &(L->width), &(L->heigth));
	labData = (char*) malloc( L->width*L->heigth);
	L->players[0]->turn = getLabyrinth(labData);
	mvwprintw(L->guiWins[0]->win, 1, 10, L->name);
	mvwprintw(L->guiWins[0]->win, 1, 25, "turn:");
	
	
	if(L->players[0]->turn==0)//if we start
	{
		L->players[0]->X=0;//curent position of the player
		L->players[0]->Y=L->heigth/2;
		L->players[0]->energy=0;
		L->players[0]->lastX=L->players[0]->X;//last position of the player
		L->players[0]->lastY=L->players[0]->Y;
		
		L->players[1]->X=L->width-1;//curent position of the player
		L->players[1]->Y=L->heigth/2;
		L->players[1]->energy=1;
		L->players[1]->lastX=L->players[1]->X;//last position of the player
		L->players[1]->lastY=L->players[1]->Y;
	}
	else//the op start
	{
		L->players[1]->X=0;//curent position of the player
		L->players[1]->Y=L->heigth/2;
		L->players[1]->energy=0;
		L->players[1]->lastX=L->players[1]->X;//last position of the player
		L->players[1]->lastY=L->players[1]->Y;
		
		L->players[0]->X=L->width-1;//curent position of the player
		L->players[0]->Y=L->heigth/2;
		L->players[0]->energy=1;
		L->players[0]->lastX=L->players[0]->X;//last position of the player
		L->players[0]->lastY=L->players[0]->Y;
	}
	
	char* e=intTostr(L->players[0]->energy);
	addStr(L->infoP1[1],"  ",e);
	e=intTostr(L->players[1]->energy);
	addStr(L->infoP2[1],"  ",e);
	free(e);
	
	
	L->players[2]->X=L->width/2;//curent position of the tresor
	L->players[2]->Y=L->heigth/2;
	L->players[2]->energy=0;
	L->players[2]->lastX=L->players[2]->X;//last position of the tresor
	L->players[2]->lastY=L->players[2]->Y;
	
	
	
	L->cases=(char **) malloc(L->heigth*sizeof(char*));
	
	
	for(i=0;i<L->heigth;i++)//get the lab in a 2dim array
	{
		L->cases[i]=(char*)malloc(L->width*sizeof(char));
		for(j=0;j<L->width;j++)
		{
			L->cases[i][j]=labData[i*L->width+j];
		}
	}
	free(labData);
	for(i=0;i<3;i++)
	{
		L->cases[L->players[i]->Y][L->players[i]->X]=i+2;
	}
	
}

int testMoveP(Map *L,int P,t_move *move)
{
	int state=0;
	switch(move->type)
	{
		case MOVE_LEFT:
			if(L->players[P]->X-1>-1)//if the player would still remain in the map
			{
				if(L->cases[L->players[P]->Y][L->players[P]->X-1]==1)
					state= -1;
			}
			else//else it has to appear in the other side
			{
				if(L->cases[L->players[P]->Y][L->width-1]==1)
					state= -1;
			}
		break;
		case MOVE_UP:
			if(L->players[P]->Y-1>-1)//if the player would still remai n in the map
			{
				if(L->cases[L->players[P]->Y-1][L->players[P]->X]==1)
					state= -1;
			}
			else
			{
				if(L->cases[L->heigth-1][L->players[P]->X]==1)
					state= -1;
			}
				
		break;
		case MOVE_DOWN:
			if(L->players[P]->Y+1<L->heigth)//if the player would still remai n in the map
			{
				if(L->cases[L->players[P]->Y+1][L->players[P]->X]==1)
					state= -1;
			}
			else
			{
				if(L->cases[0][L->players[P]->X]==1)
					state= -1;
			}
		break;
		case MOVE_RIGHT:
			if(L->players[P]->X+1<L->width)//if the player would still remai n in the map
			{
				if(L->cases[L->players[P]->Y][L->players[P]->X+1]==1)
					state= -1;
			}
			else
			{
				if(L->cases[L->players[P]->Y][0]==1)
					state= -1;
			}
		break;
	}

	return state;



}

int moveP(Map *L, int P,t_move *move)
{
	int state=0;
	if(testMoveP(L,P,move)!=-1)
	{
		switch(move->type)
		{
			case MOVE_LEFT:
				L->cases[L->players[P]->Y][L->players[P]->X]=0;
				L->players[P]->X=(L->width+L->players[P]->X-1)%L->width;	
				L->cases[L->players[P]->Y][L->players[P]->X]=2+P;
		
			break;
			case MOVE_UP:
				L->cases[L->players[P]->Y][L->players[P]->X]=0;
				L->players[P]->Y=(L->heigth+L->players[P]->Y-1)%L->heigth;
				L->cases[L->players[P]->Y][L->players[P]->X]=2+P;
								
			break;
			case MOVE_DOWN:
				L->cases[L->players[P]->Y][L->players[P]->X]=0;
				L->players[P]->Y=(L->heigth+L->players[P]->Y+1)%L->heigth;
				L->cases[L->players[P]->Y][L->players[P]->X]=2+P;
			break;
			case MOVE_RIGHT:
				L->cases[L->players[P]->Y][L->players[P]->X]=0;
				L->players[P]->X=(L->width+L->players[P]->X+1)%L->width;
				L->cases[L->players[P]->Y][L->players[P]->X]=2+P;
			break;
			default:
				state=-1;
			break;
		}
		
		
		L->players[P]->energy++;
		char* e=intTostr(L->players[P]->energy);
		if(P==0)
			addStr(L->infoP1[1],"  ",e);
		else
			addStr(L->infoP2[1],"  ",e);
			
		L->turn++;
		e=intTostr(L->turn);
		mvwprintw(L->guiWins[0]->win, 1, 32, e);
		free(e);
	}
	else
	{
		if(P==0)
			addStr(L->infoP1[5]," CANNOT MOVE","");
		else
			addStr(L->infoP2[5]," CANNOT MOVE","");
		
		state=-1;
	}
	L->players[P]->turn=1;
	L->players[(P+1)%2]->turn=0;

	return state;



}


int moveM(Map *L,int P,t_move *move)
//apply changes generate by move to the current map L
{
	int i;
	char temp;
	int width=L->width; //create to avoid many ->
	int heigth=L->heigth;
	switch (move->type)
	{
		case ROTATE_LINE_LEFT:
			temp=L->cases[move->value][0];
			for (i=0;i<width-1;i++)
			{
				L->cases[move->value][i]=L->cases[move->value][i+1];
			}
			L->cases[move->value][width-1]=temp;
			for(i=0;i<3;i++)
				if(L->players[i]->Y==move->value)
				{
					L->players[i]->X=(width+L->players[i]->X-1)%width;
				}
					
		break;

		case ROTATE_LINE_RIGHT:
			temp=L->cases[move->value][width-1];
			for (i=1;i<L->width;i++)
			{
				L->cases[move->value][width-i]=L->cases[move->value][width-1-i];
			}
			L->cases[move->value][0]=temp;
			for(i=0;i<3;i++)
				if(L->players[i]->Y==move->value)
				{
					L->players[i]->X=(width+L->players[i]->X+1)%width;
				}
		break;

		case ROTATE_COLUMN_DOWN:
			temp=L->cases[heigth-1][move->value];
			for (i=1;i<heigth;i++)
			{
				L->cases[heigth-i][move->value]=L->cases[heigth-1-i][move->value];
			}
			L->cases[0][move->value]=temp;
			for(i=0;i<3;i++)
				if(L->players[i]->X==move->value)
				{
					L->players[i]->Y=(heigth+L->players[i]->Y+1)%heigth;
				}
		break;

		case ROTATE_COLUMN_UP:
			temp=L->cases[0][move->value];
			for (i=0;i<heigth-1;i++)
			{
				L->cases[i][move->value]=L->cases[i+1][move->value];
			}
			L->cases[heigth-1][move->value]=temp;
			for(i=0;i<3;i++)
				if(L->players[i]->X==move->value)
				{
					L->players[i]->Y=(heigth+L->players[i]->Y-1)%heigth;	
				}
		break;
		default:

		break;

	}
	L->players[P]->turn=1;
	L->players[(P+1)%2]->turn=0;
	L->players[P]->energy-=5;
	char* e=intTostr(L->players[P]->energy);
	if(P==0)
		addStr(L->infoP1[1],"  ",e);
	else
		addStr(L->infoP2[1],"  ",e);
		
	L->turn++;
	e=intTostr(L->turn);
	mvwprintw(L->guiWins[0]->win, 1, 32, e);
	free(e);
	
	return 0;
}

int movement(Map *L,int P,t_move *move)
{
	if (move->type==ROTATE_COLUMN_UP || move->type==ROTATE_COLUMN_DOWN || move->type==ROTATE_LINE_LEFT ||move->type==ROTATE_LINE_RIGHT)
		moveM(L,P,move);
	else
		moveP(L,P,move);
	return 1;
}

int addStr(char *target,char *add1,char *add2)
{
	int i=0;
	while(*add1)
	{
		*target=*add1;
		target++;
		add1++;
		i++;
	}
	while(*add2)
	{
		*target=*add2;
		target++;
		add2++;
		i++;
	}
	*target='\0';
	return i;
}

char *intTostr(int nb)
{
	int i=10,n=1;
	while(nb>i){i*=10;n++;}
	
	char* nbch=(char*)malloc(sizeof(n+1));
	nbch[n]='\0';
	while(n>0)
	{
		nbch[n-1]='0'+ nb%10;
		nb/=10;
		n--;
	}
	return nbch;
}	
	
int strToint(char *nbr)
{
	int n=0,neg=0;
	char c = '0';
	if(*nbr=='-')
	{neg=1;nbr++;}
	while(*nbr)
	{
		n*=10;
		n+=*nbr-c;
		nbr++;
	}
	
	return (neg==0)?n:-n;
}	
	
	
	

