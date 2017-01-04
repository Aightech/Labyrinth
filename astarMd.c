#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct.h"
#include "gui.h"
#include "mapping.h"
#include "astarMd.h"
#include "labyrinthAPI.h"


int astarMode(Map *L)
{	
	
	t_return_code ret = MOVE_OK;		/* indicates the status of the previous move */
	t_move* myMove=(t_move*) malloc(sizeof(t_move));
	myMove->type = DO_NOTHING;
	myMove->value = 0;
	t_move* opMove=(t_move*) malloc(sizeof(t_move));
	opMove->type = DO_NOTHING;
	opMove->value = 0;
	
	
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
					if(NToGO->Y>L->players[0]->Y)
						myMove->type=MOVE_DOWN;
					else
						myMove->type=MOVE_UP;
				}
				else
				{
					if(NToGO->X>L->players[0]->X)
						myMove->type=MOVE_RIGHT;
					else
						myMove->type=MOVE_LEFT;
				}
			}
			else
				myMove->type=DO_NOTHING;
			movement(L,0,myMove);
			ret = sendMove(*myMove);
		  }
		  dispInfo(L);
		dispMap(L);
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
	Win* win=L->guiWins[0];
	int starty=12-L->heigth/2+1,startx=18-L->width/2+1;
	Node * Nact;


	Path * path=NULL;
	int i,j;
	char goalValue=4;//the value of the treasur case
	char ** nodes=(char **) malloc(L->width*L->heigth*sizeof(char*));//array of char to make easier the check of visited or not neighbor: nodes[i][j]=0=>pas check;nodes[i][j]=1=> check;
	for(i =0;i<L->heigth;i++)
	{
		nodes[i]=(char *) malloc(L->width*sizeof(char));
		for(j=0;j<L->width;j++)
			nodes[i][j]=0;
	}
		
	Node * openList=initOpenList(L,L->players[0]->X,L->players[0]->Y,nodes);
	addStr(L->infoP1[6]," step 1","");
	dispInfo(L);
	
	Nact=openList;
	wattron(win->win,COLOR_PAIR(2));
	mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
	wattroff(win->win,COLOR_PAIR(2));
	
	Node * closedList=NULL;
	Node * Ntemp=NULL;
	
	while(*(openList->ncase)!=goalValue)//if the openlist isn't empty and the current node is not the goal.
	{
		Nact=openList;
		wattron(win->win,COLOR_PAIR(2));
		mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
		wattroff(win->win,COLOR_PAIR(2));
		addStr(L->infoP1[6]," step 2","");
		dispInfo(L);
		addNeigh(L,openList,nodes);//add the neighbors of the first node of the openlist
		addStr(L->infoP1[6]," step 3","");
		dispInfo(L);
		Ntemp=openList->listNext;
		openList->listNext=closedList;
		closedList=openList;
		openList=Ntemp;
	}
	
	
	
	Nact=closedList;
	while(Nact!=NULL)
	{
		wattron(win->win,COLOR_PAIR(2));
		mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
		wattroff(win->win,COLOR_PAIR(2));
		Nact=Nact->pathParent;
	}
		
	wattron(win->win,COLOR_PAIR(3));
	mvwaddch(win->win, starty+L->players[0]->Y, startx+L->players[0]->X, 'o');
	wattroff(win->win,COLOR_PAIR(3));
	
	/*if(*(openList->ncase)==goalValue)
	{
		path=(Path*) malloc(sizeof(Path));
		path->size=openList->cost;
		path->first=extractPath(openList);//if the path is found, get the path.
	}*/
	addStr(L->infoP1[6]," step 4","");
	dispInfo(L);
	
	for(i =0;i<L->heigth;i++)
		free(nodes[i]);
	free(nodes);
	return path;
}

Node *initOpenList(Map *L,int x, int y,char ** nds) 
{
	Node* N= (Node *) malloc(sizeof(Node));
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
		N->X=x;
		N->Y=y;
		N->ncase=L->cases[N->Y]+N->X;
		N->cost=parent->cost+1;
		N->heuristic=N->cost+distNtoP(L,0,N);//dist_h(L,x,y);
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
	
	return opL;}

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
	if(N1->heuristic >= NtoAdd->heuristic)//pour l'ordre croissant ">"
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
	int dx2=(L->width - dx1);
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

int dist_h(Map *L,int x,int y) // renvoie la somme des distances horizontales et verticales d'un point au trésor pour heuristic
 { //il y a t-il besoin de faire la racine ?
	int d;
 	int Xt=L->players[2]->X;
 	int Yt=L->players[2]->Y;

	if ((d=abs(Xt-x))>L->width/2)
		d=L->width-d;
		
	if (abs(Yt-y)<L->heigth/2)
		return d=d+abs(Yt-y);
	else
		return d=d+L->heigth-abs(Yt-y);		
		
}

/*int abs(int x)  //apparement il y en a une 
{
	if (x<0)
		return -x;
	else
		return x;
}*/

/*List * add_to_list(List* list, Case c) //add the case c into list
{
	while(list->next!=NULL)
	{
	}
	
}

Node* check_lowest(List *list) //return the node with the lowest heuristique in list
{
}

int check_presence(Node* node, List *list)
{
}

Node* Astar_case(Map *L, //return the node the player has to go to
{
	List *openlist;
	List *closedlist;
	début boucle tant que openlist non vide
		prendre le plus petit élément de openlist et le mettre dans closedlist
			si noeud=trésor remonter les sources puis renvoyer la case où aller
			si noeud!=trésor rajoutez tous les voisins inexplorés (=pas dans closedlist) du noeud dans openlist si pas déjà dans la liste
	si open list vide = pas de chemin possible
}

*/



	


