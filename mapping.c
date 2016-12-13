#include <stdio.h>
#include <stdlib.h>

//#include "gui.h"
#include "struct.h"
#include "mapping.h"
#include "labyrinthAPI.h"
#include <unistd.h>



Map* initMap()
{
	Map* L=(Map *) malloc(sizeof(Map));
	L->width=21;
	L->heigth=13;
	L->cases=(char **) malloc(L->heigth*sizeof(char*));
	
	char MapI[]="000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	
	int i,j;
	for(i=0;i<L->heigth;i++)
	{
		L->cases[i]=(char*)malloc(L->width*sizeof(char));
		for(j=0;j<L->width;j++)
		{
			//printf("(%d,%d)= ",i,j);
			L->cases[i][j]=MapI[i*L->width+j];
			//scanf("%d",&p[i][j]);
			//printf("(%d,%d)= %d\n",i,j,p[i][j]);
		}
	}
	addStr(L->infoP1[0],"  Aightech","");
	addStr(L->infoP1[1],"  0","");
	for(i=2;i<10;i++)
	{
		for(j=0;j<9;j++)
		{
			L->infoP1[i][j]='o';
		}
		L->infoP1[i][9]='\0';
	}
	addStr(L->infoP2[0],"  UNKOWN","");
	addStr(L->infoP2[1],"  0","");
	for(i=2;i<10;i++)
	{
		for(j=0;j<9;j++)
		{
			L->infoP2[i][j]='o';
		}
		L->infoP1[i][9]='\0';
	}
	for(i=0;i<3;i++)
	{
		L->players[i]=(Player*) malloc(sizeof(Player));
		L->players[i]->X=0;
		L->players[i]->Y=0;
		L->players[i]->mode=0;
	}
	return L;
	
}

void getMap(Map *L)
{
	
	char* labData;						/* data of the labyrinth */
	/* connection to the server */
	connectToServer( "pc4023.polytech.upmc.fr", 1234, "Aightech");
	int i,j;
	for(i=0;i<L->heigth;i++)//delete the last cases
	{
		free(L->cases[i]);
	}
	free(L->cases);
	
	
	switch(L->players[0]->mode)
	{
		case 0:
			addStr(L->infoP1[0],"  Aightech","  (DUMB)");
			
		break;
	}
	
	char argMap[50];
	switch(L->players[1]->mode)
	{
		case 0:
			addStr(argMap,"DO_NOTHING"," timeout=10");
			addStr(L->infoP2[0],"  DO NOTHING","  (DUMB)");
			
		break;
	}
	/* wait for a game, and retrieve informations about it */
	waitForLabyrinth( argMap, L->name, &(L->width), &(L->heigth));
	labData = (char*) malloc( L->width*L->heigth);
	L->players[0]->turn = getLabyrinth(labData);
	
	
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
				if(L->players[P]->X-1>-1)//if the player would still remai n in the map
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->X--;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
				else//else it has to appear in the other side
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->X=L->width-1;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
			break;
			case MOVE_UP:
				if(L->players[P]->Y-1>-1)//if the player would still remai n in the map
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->Y--;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
				else
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->Y=L->heigth-1;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
				
			break;
			case MOVE_DOWN:
				if(L->players[P]->Y+1<L->heigth)//if the player would still remai n in the map
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->Y++;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
				else
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->Y=0;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
			break;
			case MOVE_RIGHT:
				if(L->players[P]->X+1<L->width)//if the player would still remai n in the map
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->X++;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
				else
				{
						L->cases[L->players[P]->Y][L->players[P]->X]=0;
						L->players[P]->X=0;	
						L->cases[L->players[P]->Y][L->players[P]->X]=2;
				}
			break;
		}
		L->players[P]->turn=1;
		L->players[(P+1)%2]->turn=0;
		L->players[P]->energy++;
		char* e=intTostr(L->players[P]->energy);
		if(P==0)
			addStr(L->infoP1[1],"  ",e);
		else
			addStr(L->infoP2[1],"  ",e);
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

	return state;



}


void MoveMap(Map *L,t_move move)
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


void addStr(char *target,char *add1,char *add2)
{
	while(*add1)
	{
		*target=*add1;
		target++;
		add1++;
	}
	while(*add2)
	{
		*target=*add2;
		target++;
		add2++;
	}
	*target='\0';
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
	
	
	
	
	

