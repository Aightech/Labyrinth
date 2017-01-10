#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "astarMd.h"
#include "labyrinthAPI.h"

/*! \file astarMd.h
    \brief A* related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

int astarMode(Map *L)
{	
	
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move* myMove=(t_move*) malloc(sizeof(t_move));
	myMove->type = DO_NOTHING;
	myMove->value = 0;
	t_move* opMove=(t_move*) malloc(sizeof(t_move));
	opMove->type = DO_NOTHING;
	opMove->value = 0;
	dispMap(L);
	
	while(ret==MOVE_OK)
	{
		if (L->players[0]->turn==1)//op turn	
		{
			addStr(L->infoP2[5],"                         ","");
			ret = getMove(opMove);
			movement(L,1,opMove);
		}
		else
		{
			addStr(L->infoP1[5],"                         ","");
			L->players[0]->toGoal=astarPath(L,0);
			
			if(L->players[0]->toGoal!=NULL&& L->players[0]->toGoal->first!=NULL && L->players[0]->toGoal->first->pathChild!=NULL)
			{
				Node * NToGO=L->players[0]->toGoal->first->pathChild;
				if(NToGO->X==L->players[0]->X)
				{
					if((NToGO->Y>L->players[0]->Y && NToGO->Y!=L->heigth-1) || (NToGO->Y==0&&L->players[0]->Y==L->heigth-1)||(L->players[0]->Y==L->heigth-2 && NToGO->Y==L->heigth-1))
						myMove->type=MOVE_DOWN;
					else
						myMove->type=MOVE_UP;
				}
				else
				{
					if((NToGO->X>L->players[0]->X && NToGO->X!=L->width-1) || (NToGO->X==0 && L->players[0]->X==L->width-1)||(L->players[0]->X==L->width-2 && NToGO->X==L->width-1))
						myMove->type=MOVE_RIGHT;
					else
						myMove->type=MOVE_LEFT;
				}
			}
			else
			{
				myMove->type=DO_NOTHING;
				addStr(L->infoP1[8],"no path found","");
			}
			movement(L,0,myMove);
			ret = sendMove(*myMove);
		  }
		  dispInfo(L);
		dispMap(L);
		dispPath(L);
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

	/* end the connection, because we are polite */
	closeConnection();

		
	
	
	
	return 1;
}

Path * astarPath(Map* L, int P)
{
	Path * path=NULL;
	int i,j;
	char goalValue=4;//the value of the treasur case
	char ** nodes=(char **) malloc(L->width*L->heigth*sizeof(char*));//array of char to make easier the check of visited or not neighbor: nodes[i][j]=0=>pas check;nodes[i][j]=1=> check;
	/*if (nodes==NULL) //test if the allocation is a success
	{
		printf("Malloc Error!\n");
		exit(EXIT_FAILURE); //EXIT_FAILURE is a predefined macro, opposite of EXIT_SUCCESS
	}*/
	for(i =0;i<L->heigth;i++)
	{
		nodes[i]=(char *) malloc(L->width*sizeof(char)); // we can use calloc
		/*if (nodes==NULL) //test if the allocation is a success
		{
			printf("Malloc Error!\n");
			exit(EXIT_FAILURE);
		}*/
		for(j=0;j<L->width;j++) //we don't need this if we use calloc
			nodes[i][j]=0;
	}
		
	Node * openList=initOpenList(L,L->players[0]->X,L->players[0]->Y,nodes);
	
	dispInfo(L);
	
	
	
	Node * closedList=NULL;
	Node * Ntemp=NULL;
	
	while(openList!=NULL&&*(openList->ncase)!=goalValue)//if the openlist isn't empty and the current node is not the goal.
	{
		/*Nact=openList;
		wattron(win->win,COLOR_PAIR(2));
		mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
		wattroff(win->win,COLOR_PAIR(2));*/
		dispInfo(L);
		addNeigh(L,openList,nodes);//add the neighbors of the first node of the openlist
		dispInfo(L);
		Ntemp=openList->listNext;
		openList->listNext=closedList;
		closedList=openList;
		openList=Ntemp;
	}
	
	//int ch = getch();
	
	/*Nact=closedList;
	while(Nact!=NULL)
	{
		if(openList!=NULL&&*(openList->ncase)==goalValue)
		{
			wattron(win->win,COLOR_PAIR(2));
			mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
			wattroff(win->win,COLOR_PAIR(2));
		}
		else
		{
			wattron(win->win,COLOR_PAIR(1));
			mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
			wattroff(win->win,COLOR_PAIR(1));
		}
		Nact=Nact->pathParent;
	}*/
	
	if(openList!=NULL)
	{
		
		if(*(openList->ncase)==goalValue)
		{
			path=(Path*) malloc(sizeof(Path));
			if (nodes==NULL) //test if the allocation is a success
			{
				printf("Malloc Error!\n");
				exit(EXIT_FAILURE);
				addStr(L->infoP1[6],"Malloc Error!","");
			}
			addStr(L->infoP1[7],"path found","");
			Ntemp=openList->listNext;
			openList->listNext=closedList;
			closedList=openList;
			path->size=openList->cost;
			openList=Ntemp;
			rmOList(openList);
			path->first=extractPath(closedList);//if the path is found, get the path.
		}
	}
	dispInfo(L);
	
	for(i =0;i<L->heigth;i++)
		free(nodes[i]);
	free(nodes);
	return path;
}

Node *initOpenList(Map *L,int x, int y,char ** nds) 
{
	Node* N= (Node *) malloc(sizeof(Node));
	/*if (nodes==NULL) //test if the allocation is a success
	{
		printf("Malloc Error!\n");
		exit(EXIT_FAILURE);
	}*/
	N->X=x;
	N->Y=y;
	N->ncase=L->cases[N->Y]+N->X;//this is the character of the map so it as the mapping data : wall/players
	N->cost=0;
	N->heuristic=N->cost;//+dist(L,x,y); //cost + la fonction distance au trésor 
	N->pathParent=NULL;
	N->pathChild=NULL;
	N->listNext=NULL;
	nds[N->Y][N->X]=1;
	return N;
}

Node *newNode(Map *L,int x, int y,Node * parent,char ** nds) //create a new case for a neighbour of c
{	
	Node* N=NULL;
	
	if(nds[y][x]!=1&&L->cases[y][x]!=1)
	{
		
		N=(Node *) malloc(sizeof(Node));
		/*if (nodes==NULL) //test if the allocation is a success
		{
			printf("Malloc Error!\n");
			exit(EXIT_FAILURE);
		}*/
		N->X=x;
		N->Y=y;
		
		N->ncase=L->cases[N->Y]+N->X;
		N->cost=parent->cost+1;
		N->heuristic=N->cost+distNtoP(L,2,N);//dist_h(L,x,y);
		N->pathParent=parent;
		nds[N->Y][N->X]=1;
	}
	return N;//return NULL if the node was already visted or was a wall
		
}



Node * addNeigh(Map* L,Node* opL,char** nds)// try to create a node for each neighbor, and add them to the open list.
{
	Node* N;
	int x=opL->X;
	int y=opL->Y;
	if((N=newNode(L,(x+1<L->width)?x+1:0,y,opL,nds))!=NULL)//if the node leftside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the leftside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNode(L,(x>0)?x-1:L->width-1,y,opL,nds))!=NULL)//if the node rightside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the rightside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNode(L,x,(y+1<L->heigth)?y+1:0,opL,nds))!=NULL)//if the node upside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the upside neighbor into the open list at the heuristic place it belong to.
	
	if((N=newNode(L,x,(y>0)?y-1:L->heigth-1,opL,nds))!=NULL)//if the node downside is not a wall or a already visited node.
		opL=addToList(opL,N);//put the downside neighbor into the open list at the heuristic place it belong to.
	
	
	return opL;
}

Node * extractPath(Node * clL)//start from the goal, iterativly,freing node that are not pathParent,taking pathParent node and put last node adress in its pathChild.
{	
	
	Node * Ntemp;
	while(clL->listNext!=NULL)
	{
		if(clL->pathParent==clL->listNext)
		{
			clL->pathParent->pathChild=clL;
			clL=clL->listNext;
		}
		else
		{
			Ntemp=clL->listNext->listNext;
			free(clL->listNext);
			clL->listNext=Ntemp;
		}
	}	
	return clL;
}

Node* addToList(Node *N1,Node* NtoAdd)//add a node to a list sort heuristicly increasing
{
	Node *Nact=N1;
	if(N1->heuristic > NtoAdd->heuristic)//pour l'ordre croissant ">"
	{
		
		NtoAdd->listNext = N1;
		return NtoAdd;
	}
	else
	{
		while(Nact->listNext!=NULL&&Nact->listNext->heuristic<NtoAdd->heuristic)//pour l'ordre croissant "<"
		{
			Nact=Nact->listNext;
		}
		
		NtoAdd->listNext = Nact->listNext;
		Nact->listNext = NtoAdd;
		
		return N1;
	}	
}

int distNtoP(Map *L,int P,Node *N)
{
	int dx1=(L->players[P]->X - N->X);
	dx1=(dx1>0)?dx1:-dx1;
	int dx2=(N->X + L->width - L->players[P]->X);
	dx2=(dx2>0)?dx2:-dx2;
	
	int dy1=(L->players[P]->Y - N->Y);
	dy1=(dy1>0)?dy1:-dy1;
	int dy2=(N->Y + L->heigth - L->players[P]->Y);
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


int rmOList(Node* first)
{
	Node * Ntemp;
	while(first!=NULL)
	{
		Ntemp=first->listNext;
		free(first);
		first=Ntemp;
		
	}	
	return 1;
}
