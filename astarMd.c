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
	char ** nodes=(char **) malloc(L->width*L->heigth*sizeof(char*));//array of char to make easier the check of visited or not neighbor: nodes[i][j]=0=>pas check;nodes[i][j]=1=> check;
	int i,j;
	char goalValue=4;//the value of the treasur case
	for(i =0;i<L->heigth;i++)
	{
		nodes[i]=(char *) malloc(L->width*sizeof(char));
		for(j=0;j<L->width;j++)
		{
			nodes[i][j]=0;
		}
	}
		
	Node * openList=initOpenList(L,L->players[0]->X,L->players[0]->Y,nodes);
	Node * closedList=NULL;
	
	Node * curNode=openList; //Node being process
	
	
	while(openList!=NULL&&*(curNode->ncase)==goalValue)//if the openlist isn't empty and the current node is not the goal.
	{
		openList->CListFrom=closedList;
		closedList=openList;
		//openList=popList(openList,closedList);//remove the current node, and add it on closed list
		//addNeighbors(L,openList,curNode,nodes);//add the neighbor of the curent to the openlist
		curNode=openList;//the curent node become the first of the open list
	}
	
	L->players[0]->toGoal=(Path*) malloc(sizeof(Path));
	L->players[0]->toGoal->first=NULL;
	
	//if(*(curNode->ncase)==goalValue)
	//	L->players[0]->toGoal->first=extractPath(curNode);//if the path is found, get the path.
		
		
	
	
	
	return 1;
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
		N->heuristic=N->cost;//+dist(L,x,y);
		N->pathParent=parent;
		nds[N->Y][N->X]=1;
	}
	return N;//return NULL if the node was already visted or was a wall
		
}

Node * popList(Node * opL,Node * clL)//remove the first node of the open list, and put it on the closedList.
{	
	clL->CListFrom=opl;
	return opl;}

Node * addNeigh(Map* L,Node* opL,Node* from,char** nds)// try to create a node for each neighbor, and add them to the open list.
{
	Node* N;
	//if((N=newNode(L,xUP,yUP,from,nds))!=NULL)//if the node upside is not a wall or a already visited node.
	//opL=addToList(opL,N);//put the upside neighbor into the open list at the heuristic place it belong to.
	//do it for left,right,down neighbors
	
	return opl;}

Node * extractPath(Node * clL)//start from the goal, iterativly,freing node that are not pathParent,taking pathParent node and put last node adress in its pathChild.
{	return NULL;}

/*Node* addToList(Node *N1,Node* NtoAdd)//add a node to a list sort heuristicly increasing
{
	Node *Nact=N1;
	if(N1->heuristic > MtoAdd->heuristic)//pour l'ordre croissant ">"
	{
		MtoAdd->next = M1;
		return MtoAdd;
	}
	else if(N1->ncase == MtoAdd->ncase)
	{
		free(MtoAdd);
		return M1;
	}
	else
	{
		while(Mact->next!=NULL&&Mact->next->n<MtoAdd->n)//pour l'ordre croissant "<"
		{
			Mact=Mact->next;
		}
		if(Mact->next!=NULL&&Mact->next->n==MtoAdd->n)
		{
			Mact->next->c+=MtoAdd->c;
			free(MtoAdd);
		}
		else
		{
			Maillon* next =Mact->next;
			Mact->next = MtoAdd;
			MtoAdd->next = next;
		}
		
		return M1;
	}	
}*/

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

int dist_h(Map *L,int x,int y) // renvoie la somme des distances horizontales et verticales d'un point au trésor pour heuristic
 { //il y a t-il besoin de faire la racine ?
	int d;
 	int Xt=L->players[2]->X;
 	int Yt=L->players[2]->Y;

	if (abs(Xt-x)<L->width/2)
		d=abs(Xt-x);
	else	
		d=L->width-abs(Xt-x);
		
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



	


