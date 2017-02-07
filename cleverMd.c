#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#include "struct.h"
#include "guilib.h"
#include "strlib.h"
#include "mapping.h"
#include "cleverMd.h"
#include "astarMd.h"
#include "offline.h"

#include "labyrinthAPI.h"

#define Player1 0
#define Player2 1
#define GOAL 2

/*! \file cleverMd.h
    \brief A* related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

int cleverMode(Map *L)
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
	
	L->graph=initGraph(L);
	/*dispGraph(L,L->graph);
	clock_t start,end;
	start=clock();
	int i=1000;
	while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));*/
	dispMap(L);
	
	
	
	while(ret==MOVE_OK)
	{
		if (L->players[0]->turn==1)//op turn	
		{
			if(L->offline==0)
			{
				addStr(L->infoP2[5],"                         ","");
				ret = getMove(opMove);
				movement(L,1,opMove);
				//rmPath(L->players[1]->toGoal);
				//L->players[1]->toGoal=astarPath(L,1);
			}
			else
			{
				addStr(L->infoP2[5],"                         ","");
				getMoveOff(L,1,opMove);
				ret =movement(L,1,opMove);
			}
		}
			
		else
		{
			addStr(L->infoP1[5],"                         ","");
			cleverMv(L, 0,myMove);//get the astar move to do
			
			if(L->offline==0)
			{
				movement(L,0,myMove);
				sendComment(L->comments[rand()%5]);
				ret = sendMove(*myMove);
			}
			else
				ret =movement(L,0,myMove);
		  }
		
		
		dispInfo(L);
		dispMap(L);
		dispPath(L);
		//int ch = getch();
		//endwin();
		  //printLabyrinth();
		  
		  
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

	
	return 1;
}

Graph * initGraph(Map *L)
{
	Graph * graph=(Graph *) malloc(sizeof(Graph));
	
	graph->width=L->width;
	graph->heigth=L->heigth;
	graph->xG=L->players[2]->X;
	graph->yG=L->players[2]->Y;
	graph->depth=0;
	int i,j;
	graph->grid=(int**)malloc(graph->heigth*sizeof(int*));
	for(i=0;i<L->heigth;i++)
	{
		graph->grid[i]=(int*)malloc(graph->width*sizeof(int));
		for(j=0;j<L->width;j++)
			if(L->cases[i][j]!=2&&L->cases[i][j]!=3)
				graph->grid[i][j]=L->cases[i][j];
	}
	
	//graph->rotGraph =(Graph ***) malloc(4*sizeof(Graph**));
	graph->rotGraph[0] =(Graph **) calloc(L->heigth,sizeof(Graph*));//LINE_LEFT
	graph->rotGraph[1] =(Graph **) calloc(L->heigth,sizeof(Graph*));//LINE_RIGHT
	graph->rotGraph[2] =(Graph **) calloc(L->width,sizeof(Graph*));//COLUMN_UP
	graph->rotGraph[3] =(Graph **) calloc(L->width,sizeof(Graph*));//COLUMN_DOWN
	
	dijkstraMarking(graph,graph->xG,graph->yG);
	
	return graph;
}

Graph * computeGraphRot(Graph * graph, int type, int value)
{
	//endwin();
	if(graph->rotGraph[type][value]!=NULL)
	{
		//printf("already compute\n");
		return graph->rotGraph[type][value];
	}	
	//printf("type:%d|value:%d|depth:%d\n",type,value,graph->depth);
	Graph * graphR=(Graph *) malloc(sizeof(Graph));
	graph->rotGraph[type][value]=graphR;
	int i,j;
	int width=graph->width; //create to avoid many ->
	int heigth=graph->heigth;
	
	graphR->width=width;
	graphR->heigth=heigth;
	graphR->depth=graph->depth+1;
	graphR->width=width;
	graphR->xG=graph->xG;
	graphR->yG=graph->yG;
	
	graphR->grid=(int**)malloc(heigth*sizeof(int*));
	for(i=0;i<heigth;i++)
	{
		graphR->grid[i]=(int*)malloc(width*sizeof(int));
		for(j=0;j<width;j++)
			graphR->grid[i][j]=graph->grid[i][j];
	}
	
	
	
	graphR->rotGraph[0] =(Graph **) calloc(heigth,sizeof(Graph*));//LINE_LEFT
	graphR->rotGraph[1] =(Graph **) calloc(heigth,sizeof(Graph*));//LINE_RIGHT
	graphR->rotGraph[2] =(Graph **) calloc(width,sizeof(Graph*));//COLUMN_UP
	graphR->rotGraph[3] =(Graph **) calloc(width,sizeof(Graph*));//COLUMN_DOWN
	
	
	
	char temp;
	
	
	switch (type)
	{
		case ROTATE_LINE_LEFT:
			graphR->rotGraph[1][value]=graph;
			temp=graphR->grid[value][0];
			for (i=0;i<width-1;i++)
			{
				graphR->grid[value][i]=graphR->grid[value][i+1];
			}
			graphR->grid[value][width-1]=temp;
			if(graphR->yG==value)
				graphR->xG=(width+graphR->xG+1)%width;
					
		break;

		case ROTATE_LINE_RIGHT:
			graphR->rotGraph[0][value]=graph;
			temp=graphR->grid[value][width-1];
			for (i=1;i<width;i++)
			{
				graphR->grid[value][width-i]=graphR->grid[value][width-1-i];
			}
			graphR->grid[value][0]=temp;
			if(graphR->yG==value)
				graphR->xG=(width+graphR->xG-1)%width;
			
		break;
		
		case ROTATE_COLUMN_UP:
			graphR->rotGraph[3][value]=graph;
			temp=graphR->grid[0][value];
			for (i=0;i<heigth-1;i++)
			{
				graphR->grid[i][value]=graphR->grid[i+1][value];
			}
			graphR->grid[heigth-1][value]=temp;
			if(graphR->xG==value)
				graphR->yG=(heigth+graphR->yG-1)%heigth;
			
		break;
		
		case ROTATE_COLUMN_DOWN:
			graphR->rotGraph[2][value]=graph;
			temp=graphR->grid[heigth-1][value];
			for (i=1;i<heigth;i++)
			{
				graphR->grid[heigth-i][value]=graphR->grid[heigth-1-i][value];
			}
			graphR->grid[0][value]=temp;
			if(graphR->xG==value)
				graphR->yG=(heigth+graphR->yG+1)%heigth;
			
		break;

	}
	dijkstraMarking(graphR,graphR->xG,graphR->yG);
	
	return graphR;
	
	
}


void cleverMv(Map* L, int P,t_move* move)
{
	int x=L->players[P]->X;
	int y=L->players[P]->Y;
	int depth=4,i,j,k;
	//printf("\n\n\tx:%d\ty:%d\n",x,y);
	Movement *ch;
	Movement *mv=(Movement *) malloc(sizeof(Movement));
	mv->childs=NULL;
	mv->parent = NULL;
	mv->cost=0;
	mv->move.type= DO_NOTHING;
	mv->energy[P]=L->players[P]->energy;
	mv->energy[(P+1)%2]=L->players[(P+1)%2]->energy;
	mv->graph = L->graph;
	
	mv->map=mv->graph->grid;
	
	mv->pos[0][0]=L->players[0]->X;
	mv->pos[0][1]=L->players[0]->Y;
	mv->pos[1][0]=L->players[1]->X;
	mv->pos[1][1]=L->players[1]->Y;
	mv->pos[2][0]=L->players[2]->X;
	mv->pos[2][1]=L->players[2]->Y;
	//printf("\n\nx:%d\ty:%d\n",mv->pos[0][0],mv->pos[0][1]);
	
	
	
	
	
	//endwin();
	int dim[4]={L->heigth,L->heigth,L->width,L->width};
	
	addStr(L->infoP1[4]," RIGHT:NO","");
	addStr(L->infoP1[5]," LEFT:NO","");
	addStr(L->infoP1[6]," DOWN:NO","");
	addStr(L->infoP1[7]," UP:NO","");
	addStr(L->infoP1[8]," STOP:NO","");
	//dispInfo(L);
	
	
	
	if((ch=initMovement(mv,P,MOVE_UP,x,(y>0)?y-1:L->heigth-1))!=NULL)//if the node upside is not a wall or a already visited node.
	{
		addStr(L->infoP1[7]," UP:OK","");
		//dispInfo(L);
		ch->value=Min(L,depth-1,ch,P);
		mvwprintw(L->guiWins[1]->win, 3+7, 11, "Cost = %d    ", ch->value);
		mv->childs=addToListMAX(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
	}
	if((ch=initMovement(mv,P,MOVE_DOWN,x,(y+1<L->heigth)?y+1:0))!=NULL)//if the node downside is not a wall or a already visited node.
	{
		addStr(L->infoP1[6]," DOWN:OK","");
		//dispInfo(L);
		ch->value=Min(L,depth-1,ch,P);
		mvwprintw(L->guiWins[1]->win, 3+6, 11, "Cost = %d    ", ch->value);
		mv->childs=addToListMAX(mv->childs,ch);//put the downside neighbor into the open list at the heuristic place it belong to.
		
		
	}
	if((ch=initMovement(mv,P,MOVE_LEFT,(x>0)?x-1:L->width-1,y))!=NULL)//if the node leftside is not a wall or a already visited node.
	{
		addStr(L->infoP1[5]," LEFT:OK","");
		//dispInfo(L);
		ch->value=Min(L,depth-1,ch,P);
		mvwprintw(L->guiWins[1]->win, 3+5, 11, "Cost = %d    ", ch->value);
		mv->childs=addToListMAX(mv->childs,ch);//put the rightside neighbor into the open list at the heuristic place it belong to.
		//L->cases[y][(x>0)?x-1:L->width-1]='M'+ch->value;
		
	}
	if((ch=initMovement(mv,P,MOVE_RIGHT,(x+1<L->width)?x+1:0,y))!=NULL)//if the node rightside is not a wall or a already visited node.
	{
		addStr(L->infoP1[4]," RIGHT:OK","");
		//dispInfo(L);
		ch->value=Min(L,depth-1,ch,P);
		mvwprintw(L->guiWins[1]->win, 3+4, 11, "Cost = %d    ", ch->value);
		
		mv->childs=addToListMAX(mv->childs,ch);//put the leftside neighbor into the open list at the heuristic place it belong to.
		//L->cases[y][(x+1<L->width)?x+1:0]='M'+ch->value;
		
	}
	if((ch=initMovement(mv,P,DO_NOTHING,x,y))!=NULL)//if the node rightside is not a wall or a already visited node.
	{	
		addStr(L->infoP1[8]," STOP:OK","");
		//dispInfo(L);
		ch->value=Min(L,depth-1,ch,P);
		mv->childs=addToListMAX(mv->childs,ch);//put the leftside neighbor into the open list at the heuristic place it belong to.
		mvwprintw(L->guiWins[1]->win, 3+8, 11, "Cost = %d    ", ch->value);
		//L->cases[y][(x+1<L->width)?x+1:0]='M'+ch->value;
		
	}
	
	
	/*printf("p1:x=%d\ty=%d\n",mv->pos[0][0],mv->pos[0][1]);
	printf("p2:x=%d\ty=%d\n",mv->pos[1][0],mv->pos[1][1]);
	printf("Go:x=%d\ty=%d\n",mv->pos[2][0],mv->pos[2][1]);*/
	if(mv->energy[P]>4)
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<4;j++)
			{
				for(k=-1;k<2;k++)
				{
					if((ch=initMovementRot(mv,P,j,(dim[j]+mv->pos[i][(j<2)?1:0]+k)%dim[j]))!=NULL)//if the node upside is not a wall or a already visited node.
					{
						//addStr(L->infoP1[3]," ROT=","");
						
						ch->value=Min(L,depth-1,ch,P);
						
						
						
						mv->childs=addToListMAX(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
					}
				}
			}
		}
	}
	
	addStr(L->infoP1[9],"","");
	//dispInfo(L);
	if(mv->childs->move.type<4)
	{
		mvwprintw(L->guiWins[1]->win, 3+9,3, "rot Cost = %d ",mv->childs->value);
		/*dispGraph(L,mv->childs->graph);
		dispSeqMov(L,mv->childs,P);*/
	}
	
	//dispMap(L);
	getch();
	
	L->graph=mv->childs->graph;
	
	move->type=mv->childs->move.type;
	move->value=mv->childs->move.value;
	freeMovement(mv);
	
	
}

int Max(Map *L,int depth,Movement* mv,int P)//return the best this move could lead to
{
	int M,i,j,k;
	if(depth > 0)
	{
		Movement *ch;
		int x=mv->pos[P][0];
		int y=mv->pos[P][1];
		
		if(x==L->players[2]->X && y==L->players[2]->Y)
			return evaluate(L,mv,P);
		
		if((ch=initMovement(mv,P,DO_NOTHING,x,y))!=NULL)//if the node leftside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Min(L,depth-1,ch,P);
			mv->childs=addToListMAX(mv->childs,ch);
		}
		
		if((ch=initMovement(mv,P,MOVE_LEFT,(x+1<L->width)?x+1:0,y))!=NULL)//if the node leftside is not a wall or a already visited node.
		{
			//dispMap(L);
			//printf("left\n");
			ch->value=Min(L,depth-1,ch,P);
			//*(ch->node)='0'+ch->value%10;
			mv->childs=addToListMAX(mv->childs,ch);//put the leftside neighbor into the open list at the heuristic place it belong to.
			//printf("bouh\n");
		}
		if((ch=initMovement(mv,P,MOVE_RIGHT,(x>0)?x-1:L->width-1,y))!=NULL)//if the node rightside is not a wall or a already visited node.
		{
			//dispMap(L);
			//printf("right\n");
			ch->value=Min(L,depth-1,ch,P);
			mv->childs=addToListMAX(mv->childs,ch);//put the rightside neighbor into the open list at the heuristic place it belong to.
			//printf("bouh\n");
		}
		if((ch=initMovement(mv,P,MOVE_UP,x,(y+1<L->heigth)?y+1:0))!=NULL)//if the node upside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Min(L,depth-1,ch,P);
			mv->childs=addToListMAX(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
		}
		if((ch=initMovement(mv,P,MOVE_DOWN,x,(y>0)?y-1:L->heigth-1))!=NULL)//if the node downside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Min(L,depth-1,ch,P);
			
			mv->childs=addToListMAX(mv->childs,ch);//put the downside neighbor into the open list at the heuristic place it belong to.
		}
		
		if(mv->energy[P]>4)
		{
			int dim[4]={mv->graph->heigth,mv->graph->heigth,mv->graph->width,mv->graph->width};
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					for(k=-1;k<2;k++)
					{
						if((ch=initMovementRot(mv,P,j,(dim[j]+mv->pos[i][(j<2)?1:0]+k)%dim[j]))!=NULL)//if the node upside is not a wall or a already visited node.
						{
							ch->value=Min(L,depth-1,ch,P);
							mv->childs=addToListMAX(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
						}
					}
				}
			}
		}
		
		M=mv->childs->value;
	}
	else
	{	
		
		M=evaluate(L,mv,P);
		//printf("M=%d\t\n",M);
	}
	return M;
	
	
}

int Min(Map * L,int depth,Movement* mv,int P)//return the best this move could lead to
{
	int M,i,j,k;
	//printf("min:%d\n",depth);
	if(depth > 0)
	{
		Movement *ch;
		int x=mv->pos[(P+1)%2][0];
		int y=mv->pos[(P+1)%2][1];
		
		if(x==L->players[2]->X && y==L->players[2]->Y)
			return evaluate(L,mv,P);
		
		if((ch=initMovement(mv,(P+1)%2,DO_NOTHING,x,y))!=NULL)//if the node leftside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Max(L,depth-1,ch,P);
			mv->childs=addToListMIN(mv->childs,ch);
		}
		
		if((ch=initMovement(mv,(P+1)%2,MOVE_LEFT,(x+1<L->width)?x+1:0,y))!=NULL)//if the node leftside is not a wall or a already visited node.
		{
			//dispMap(L);
			//printf("left\n");
			ch->value=Max(L,depth-1,ch,P);
			//printf("addchild\n");
			mv->childs=addToListMIN(mv->childs,ch);//put the leftside neighbor into the open list at the heuristic place it belong to.
			
			//printf("bouh\n");
		}
		if((ch=initMovement(mv,(P+1)%2,MOVE_RIGHT,(x>0)?x-1:L->width-1,y))!=NULL)//if the node rightside is not a wall or a already visited node.
		{
			//dispMap(L);
			//printf("right\n");
			ch->value=Max(L,depth-1,ch,P);
			//printf("addchild\n");
			mv->childs=addToListMIN(mv->childs,ch);//put the rightside neighbor into the open list at the heuristic place it belong to.
			
			//rintf("bouh\n");
		}
		if((ch=initMovement(mv,(P+1)%2,MOVE_UP,x,(y+1<L->heigth)?y+1:0))!=NULL)//if the node upside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Max(L,depth-1,ch,P);
			mv->childs=addToListMIN(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
			//dispMap(L);
		}
		if((ch=initMovement(mv,(P+1)%2,MOVE_DOWN,x,(y>0)?y-1:L->heigth-1))!=NULL)//if the node downside is not a wall or a already visited node.
		{
			//dispMap(L);
			ch->value=Max(L,depth-1,ch,P);
			mv->childs=addToListMIN(mv->childs,ch);//put the downside neighbor into the open list at the heuristic place it belong to.
			//dispMap(L);
		}
		
		if(mv->energy[(P+1)%2]>4)
		{
			int dim[4]={mv->graph->heigth,mv->graph->heigth,mv->graph->width,mv->graph->width};
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					for(k=-1;k<2;k++)
					{
						if((ch=initMovementRot(mv,P,j,(dim[j]+mv->pos[i][(j<2)?1:0]+k)%dim[j]))!=NULL)//if the node upside is not a wall or a already visited node.
						{
							ch->value=Max(L,depth-1,ch,P);
							mv->childs=addToListMIN(mv->childs,ch);//put the upside neighbor into the open list at the heuristic place it belong to.
						}
					}
				}
			}
		}
		
		M=mv->childs->value;
		
	}
	else
	{
		M=evaluate(L,mv,P);
		//printf("M=%d\t\n",M);
	}
	return M;
	
	
}

void initChilds(Movement *mv)
{
}
void freeMovement(Movement *mv)
{
	if(mv!=NULL)
	{
		Movement *ch;
		while(mv->childs != NULL)
		{
			ch=mv->childs->listNext;
			freeMovement(mv->childs);
			mv->childs=ch;
		}
	}
		
}
Movement *initMovement(Movement *parent,int P,int moveType,int x, int y)
{
	
	Movement *mv=NULL;
	//printf("x:%d\ty:%d\n",x,y);
	/*clock_t start,end;
	start=clock();
	int i=50;
	while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));*/
	if(parent->graph->grid[y][x]!=1)
	{
		mv=(Movement *) malloc(sizeof(Movement));
		*mv=*parent;
		
		mv->cost++;
		mv->childs=NULL;
		mv->listNext=NULL;
		mv->parent = parent;
		mv->move.type= moveType;
		//parent->map[y][x]=4;
		//mv->node=parent->map[y]+x;
		mv->energy[P]++;
		
		mv->pos[P][0]=x;
		mv->pos[P][1]=y;
	}
	return mv;//return NULL if the node was already visted or was a wall
		
}

Movement *initMovementRot(Movement *parent,int P,int moveType,int value)
{
	
	// *mv=NULL;
	//printf("x:%d\ty:%d\n",x,y);
	/*clock_t start,end;
	start=clock();
	int i=50;
	while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));*/
	
	Movement *mv=(Movement *) malloc(sizeof(Movement));
	*mv=*parent;
	int heigth=mv->graph->heigth;
	int width=mv->graph->width;
	int i;
	mv->graph=computeGraphRot(mv->graph,moveType,value);
	
	
	mv->cost=parent->cost+1;;
	mv->childs=NULL;
	mv->listNext=NULL;
	mv->parent = parent;
	mv->move.type= moveType;
	mv->move.value= value;
	
	//mv->node=parent->map[y]+x;
	mv->energy[P]-=5;
	switch(moveType)
	{
		case ROTATE_LINE_LEFT:
			for(i=0;i<3;i++)
				if(mv->pos[i][1]==value)
					mv->pos[i][0]=(width+mv->pos[i][0]-1)%width;
		break;
		case ROTATE_LINE_RIGHT:
			for(i=0;i<3;i++)
				if(mv->pos[i][1]==value)
					mv->pos[i][0]=(width+mv->pos[i][0]+1)%width;
		break;
		case ROTATE_COLUMN_UP:
			for(i=0;i<3;i++)
				if(mv->pos[i][0]==value)
					mv->pos[i][1]=(heigth+mv->pos[i][1]-1)%heigth;
		break;
		case ROTATE_COLUMN_DOWN:
			for(i=0;i<3;i++)
				if(mv->pos[i][0]==value)
					mv->pos[i][1]=(heigth+mv->pos[i][1]+1)%heigth;
		break;
		
	}
	
	return mv;//return NULL if the node was already visted or was a wall
		
}

void dijkstraMarking(Graph *G,int x, int y)
{
	//TODO put -1 everywhere
	//endwin();
	//printf("depth:%d\n",G->depth);
	char ** nodes=(char **) malloc(G->width*G->heigth*sizeof(char*));//array of char to make easier the check of visited or not neighbor: nodes[i][j]=0=>pas check;nodes[i][j]=1=> check;
	if (nodes==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE); //EXIT_FAILURE is a predefined macro, opposite of EXIT_SUCCESS
	int i,j;
	for(i =0;i<G->heigth;i++)
	{
		nodes[i]=(char *) calloc(G->width,sizeof(char)); // we can use calloc
		if (nodes[i]==NULL) //test if the allocation is a success
			exit(EXIT_FAILURE);
		for(j=0;j<G->width;j++)
			if(G->grid[i][j]!=1)
				G->grid[i][j]=1000;
	}
	
	DijkstraNode * openList = (DijkstraNode *) malloc(sizeof(DijkstraNode));
	if (openList==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE);
		
	openList->X=x;
	openList->Y=y;
	openList->cost=0;
	G->grid[y][x]=2;
	openList->listNext=NULL;
	nodes[y][x]=1;
	
	//printf("ok\n");
	while(openList!=NULL)//if the openlist isn't empty and the current node is not the goal.
	{
		openList=addNeighD(G,openList,nodes);//add the neighbors of the first node of the openlist, and 
	}
	
	for(i =0;i<G->heigth;i++)
		free(nodes[i]);
	free(nodes);
	
}

DijkstraNode * addNeighD(Graph *G,DijkstraNode * opL,char** nds)// try to create a node for each neighbor, and add them to the open list.
{
	DijkstraNode * N;
	DijkstraNode * actN=opL;
	
	int x=opL->X;
	int y=opL->Y;
	
	opL=opL->listNext;
	
	if((N=newNodeD(G,(x+1<G->width)?x+1:0,y,actN->cost,nds))!=NULL)//if the node rightside is not a wall or a already visited node.
		opL=addToListCost(opL,N);//put the leftside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeD(G,(x>0)?x-1:G->width-1,y,actN->cost,nds))!=NULL)//if the node leftside is not a wall or a already visited node.
		opL=addToListCost(opL,N);//put the rightside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeD(G,x,(y+1<G->heigth)?y+1:0,actN->cost,nds))!=NULL)//if the node downside is not a wall or a already visited node.
		opL=addToListCost(opL,N);//put the upside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeD(G,x,(y>0)?y-1:G->heigth-1,actN->cost,nds))!=NULL)//if the node upside is not a wall or a already visited node.
		opL=addToListCost(opL,N);//put the downside neighbor into the open list at the heuristic place it belong to.
		
	free(actN);
	
	return opL;
}

DijkstraNode *newNodeD(Graph *G,int x, int y,int costParent,char ** nds) //create a new case for a neighbour of c
{	
	DijkstraNode* N=NULL;
	if(nds[y][x]!=1&&G->grid[y][x]!=1)
	{
		
		N=(DijkstraNode *) malloc(sizeof(DijkstraNode));
		if (N==NULL) //test if the allocation is a success
			exit(EXIT_FAILURE);
		
		N->X=x;
		N->Y=y;
		N->cost=costParent+1;
		nds[y][x]=1;
		N->listNext=NULL;
		G->grid[y][x]=2+N->cost;
		/*L->cases[y][x]='0' + N->cost%10;
		dispMap(L);
		clock_t start,end;
		start=clock();
		int i=50;
		while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));*/
		
	}
	return N;//return NULL if the node was already visted or was a wall
		
}

DijkstraNode * addToListCost(DijkstraNode *N1,DijkstraNode* NtoAdd)//add a node to a list sort cost increasing
{
	DijkstraNode *Nact=N1;
	if(N1==NULL)
		return NtoAdd;	
	if(N1->cost > NtoAdd->cost)//pour l'ordre croissant ">"
	{
		NtoAdd->listNext = N1;
		return NtoAdd;
	}
	else
	{
		while(Nact->listNext!=NULL&&Nact->listNext->cost<NtoAdd->cost)//pour l'ordre croissant "<"
		{
			Nact=Nact->listNext;
		}
		
		NtoAdd->listNext = Nact->listNext;
		Nact->listNext = NtoAdd;
		
		return N1;
	}	
}


int evaluate(Map *L,Movement *M,int P)
{
	//printf("ad:%p\tx:%d\ty:%d\tv1:%d \t v2:%d\tv1-v2:%d\n",M->pos,M->pos[0][0],M->pos[0][1],M->graph->grid[M->pos[1][1]][M->pos[1][0]],M->graph->grid[M->pos[0][1]][M->pos[0][0]],M->graph->grid[M->pos[1][1]][M->pos[1][0]]-M->graph->grid[M->pos[0][1]][M->pos[0][0]]);
	return M->graph->grid[M->pos[1][1]][M->pos[1][0]]-M->graph->grid[M->pos[0][1]][M->pos[0][0]]-M->cost;//M->graph->grid[M->pos[1][1]][M->pos[1][0]]//astarDistMtoG(L,M,1,2)-astarDistMtoG(L,M,0,2);//distMtoG(L,M,(P+1)%2,2)//-distMtoG(L,M,P,2);
}

int distMtoG(Map *L,Movement *M,int P, int G)
{
	int dx1=(L->players[G]->X - M->pos[P][0]);
	dx1=(dx1>0)?dx1:-dx1;
	int dx2=(M->pos[P][0] + L->width - L->players[G]->X);
	dx2=(dx2>0)?dx2:-dx2;
	
	int dy1=(L->players[G]->Y - M->pos[P][1]);
	dy1=(dy1>0)?dy1:-dy1;
	int dy2=(M->pos[P][1] + L->heigth - L->players[G]->Y);
	dy2=(dy2>0)?dy2:-dy2;
	
	if(dx1<dx2)
	{
		if(dy1<dy2)
			return dx1+dy1;
		else
			return dx1+dy2;
	}
	else	
	{
		if(dy1<dy2)
			return dx2+dy1;
		else
			return dx2+dy2;
	}	
		
}

int astarDistMtoG(Map *L,Movement *M,int P, int G)
{
	int i,j;
	//char goalValue=4;//the value of the treasur case
	char ** nodes=(char **) malloc(M->graph->width*M->graph->heigth*sizeof(char*));//array of char to make easier the check of visited or not neighbor: nodes[i][j]=0=>pas check;nodes[i][j]=1=> check;
	if (nodes==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE); //EXIT_FAILURE is a predefined macro, opposite of EXIT_SUCCESS
		
	for(i =0;i<M->graph->heigth;i++)
	{
		nodes[i]=(char *) malloc(M->graph->width*sizeof(char)); // we can use calloc
		if (nodes[i]==NULL) //test if the allocation is a success
			exit(EXIT_FAILURE);
			
		for(j=0;j<M->graph->width;j++) //we don't need this if we use calloc
			nodes[i][j]=0;
	}
		
	Node * openList=initOpenList(L,M->pos[P][0],M->pos[P][1],nodes);
	//printf("from x=%d;y=%d",M->pos[P][0],M->pos[P][0]);
	//dispInfo(L);
	
	int xG=L->players[G]->X;
	int yG=L->players[G]->Y;
	if(M->pos[P][0]==xG && M->pos[P][1]==yG)
		return 0;
	
	Node * closedList=NULL;
	Node * Ntemp=NULL;
	
	while(openList!=NULL && !(openList->X==xG && openList->Y==yG))//if the openlist isn't empty and the current node is not the goal.
	{
		addNeigh(L,openList,nodes);//add the neighbors of the first node of the openlist
		Ntemp=openList->listNext;
		openList->listNext=closedList;
		closedList=openList;
		openList=Ntemp;
		
	}
	

	
	for(i =0;i<L->heigth;i++)
		free(nodes[i]);
	free(nodes);
	if(openList!=NULL)
	{
		
		if(openList->X==xG && openList->Y==yG)
		{
			//printf("\nsize of %dcases",openList->cost);
			int cost=openList->cost;
			rmOList(openList);
			rmOList(closedList);
			return cost;
		}
	}
	mvwprintw(L->guiWins[1]->win, 3+8, 11, "%s", "issue");
	return 10000;
}

Node *initOpenListC(Movement *M,int x, int y,char ** nds) 
{
	Node* N= (Node *) malloc(sizeof(Node));
	if (N==NULL) //test if the allocation is a success
		exit(EXIT_FAILURE);
		
	N->X=x;
	N->Y=y;
	//N->ncase=M->graph->grid[N->Y]+N->X;//this is the character of the map so it as the mapping data : wall/players
	N->cost=0;
	N->heuristic=N->cost;//+dist(L,x,y); //cost + la fonction distance au trésor 
	N->pathParent=NULL;
	N->pathChild=NULL;
	N->listNext=NULL;
	nds[N->Y][N->X]=1;
	return N;
}

Node *newNodeC(Movement *M,int x, int y,Node * parent,char ** nds) //create a new case for a neighbour of c
{	
	Node* N=NULL;
	int ** cases=M->graph->grid;
	if(nds[y][x]!=1&&cases[y][x]!=1)
	{
		
		N=(Node *) malloc(sizeof(Node));
		if (N==NULL) //test if the allocation is a success
			exit(EXIT_FAILURE);
		
		N->X=x;
		N->Y=y;
		
		//N->ncase=cases[N->Y]+N->X;
		N->cost=parent->cost+1;
		/*L->cases[y][x]='0' + N->cost%10;
		dispMap(L);
		clock_t start,end;
		start=clock();
		int i=50;
		while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));*/
		N->heuristic=N->cost+distNtoPC(M,2,N);//dist_h(L,x,y);
		N->pathParent=parent;
		N->pathChild=NULL;
		nds[N->Y][N->X]=1;
	}
	return N;//return NULL if the node was already visted or was a wall
		
}



Node * addNeighC(Movement *M,Node* opL,char** nds)// try to create a node for each neighbor, and add them to the open list.
{
	Node* N;
	int x=opL->X;
	int y=opL->Y;
	if((N=newNodeC(M,(x+1< M->graph->width)?x+1:0,y,opL,nds))!=NULL)//if the node rightside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the leftside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeC(M,(x>0)?x-1: M->graph->width-1,y,opL,nds))!=NULL)//if the node leftside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the rightside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeC(M,x,(y+1< M->graph->heigth)?y+1:0,opL,nds))!=NULL)//if the node downside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the upside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNodeC(M,x,(y>0)?y-1: M->graph->heigth-1,opL,nds))!=NULL)//if the node upside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the downside neighbor into the open list at the heuristic place it belong to.
	
	
	return opL;
}

int distNtoPC(Movement *M,int P,Node *N)
{
	int dx1=(M->pos[P][0] - N->X);
	dx1=(dx1>0)?dx1:-dx1;
	int dx2=(N->X + M->graph->width - M->pos[P][0]);
	dx2=(dx2>0)?dx2:-dx2;
	
	int dy1=(M->pos[P][1] - N->Y);
	dy1=(dy1>0)?dy1:-dy1;
	int dy2=(N->Y + M->graph->heigth -M->pos[P][1]);
	dy2=(dy2>0)?dy2:-dy2;
	
	if(dx1<dx2)
	{
		if(dy1<dy2)
			return dx1+dy1;
		else
			return dx1+dy2;
	}
	else	
	{
		if(dy1<dy2)
			return dx2+dy1;
		else
			return dx2+dy2;
	}	
		
}

Movement *addToListMIN(Movement * M1,Movement * MtoAdd)//smallest value first
{
	//printf("sort...min\n");
	if(M1==NULL)
	{
		//printf("NULL\n");
		return MtoAdd;
	}
	if(MtoAdd==NULL)
	{
		//printf("shit\n");
	}
	Movement *Mact=M1;
	if(M1->value > MtoAdd->value)//pour l'ordre croissant ">"
	{
		//printf("maybe\n");
		MtoAdd->listNext = M1;
		return MtoAdd;
	}
	else
	{	
		//printf("maybe\n");
		while(Mact->listNext!=NULL&&Mact->listNext->value<MtoAdd->value)//pour l'ordre croissant "<"
		{
			//printf("-%d-\n",Mact->listNext->value);
			Mact=Mact->listNext;
		}
		//printf("\n");
		
		MtoAdd->listNext = Mact->listNext;
		Mact->listNext = MtoAdd;
		
		return M1;
	}	
}

Movement *addToListMAX(Movement * M1,Movement * MtoAdd)//biggest value first
{
	//printf("sort...max\n");
	if(M1==NULL)
	{
		//printf("NULL\n");
		return MtoAdd;
	}
	if(MtoAdd==NULL)
	{
		//printf("shit\n");
	}
	Movement *Mact=M1;
	if(M1->value < MtoAdd->value)//pour l'ordre croissant ">"
	{
		
		MtoAdd->listNext = M1;
		return MtoAdd;
	}
	else
	{
		while(Mact->listNext!=NULL&&Mact->listNext->value > MtoAdd->value)//pour l'ordre croissant "<"
		{
			//printf("hey\n");
			//printf("-%d-\n",Mact->listNext->value);
			Mact=Mact->listNext;
			
		}
		//printf("\n");
		MtoAdd->listNext = Mact->listNext;
		Mact->listNext = MtoAdd;
		
		return M1;
	}	
}


Path * cleverPath(Map* L, int P)
{
	
	return NULL;
}


