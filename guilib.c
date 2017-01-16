#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "struct.h"
#include "guilib.h"
#include "mapping.h"
#include "strlib.h"

/*! \file guilib.c
    \brief GUI related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/


void initGUI(Map * L)
{
	initscr();
	clear();
	noecho();
	start_color();
	cbreak();	/* Line buffering disabled. pass on everything */
	keypad(stdscr, TRUE);
	refresh();

	mvprintw( 1, 1, "%s","  _____              _                    _       _                 _                 ");
	mvprintw( 2, 1, "%s"," |  __ \\            (_)                  | |     (_)               | |                ");
	mvprintw( 3, 1, "%s"," | |  | | ___  _ __  _  ___  _ __     ___| |_     _  __ _ _ __ ___ | |__   ___  _ __  ");
	mvprintw( 4, 1, "%s"," | |  | |/ _ \\| '_ \\| |/ _ \\| '_ \\   / _ \\ __|   | |/ _` | '_ ` _ \\| '_ \\ / _ \\| '_ \\ ");
	mvprintw( 5, 1, "%s"," | |__| | (_) | | | | | (_) | | | | |  __/ |_    | | (_| | | | | | | |_) | (_) | | | |");
	mvprintw( 6, 1, "%s"," |_____/ \\___/|_| |_| |\\___/|_| |_|  \\___|\\__|   | |\\__,_|_| |_| |_|_.__/ \\___/|_| |_|");
	mvprintw( 7, 1, "%s","                   _/ |                         _/ |                                  ");
	mvprintw( 8, 1, "%s","                  |__/                         |__/                                   ");
	mvprintw( 10, 1, "%s","                                     < PRESS ANY KEY >                                 ");
	
	getch();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	
	int i;
	
	/*Allocation*/
	L->guiWins=(Win **)malloc(nbrW*sizeof(Win *));
	for(i = 0; i < nbrW; ++i)
		L->guiWins[i]=(Win *)malloc(nbrW*sizeof(Win));	
	/*Definition*/
	L->guiWins[0]->win=newwin(25, 40, 0, 0);//Map windows
	addStr(L->guiWins[0]->label,"Map:  ",L->name);
	L->guiWins[0]->numButt=0;
	
	L->guiWins[1]->win=newwin(16, 40, 0, 40);//Info player 1
	addStr(L->guiWins[1]->label,"Information Player 1:","");
	L->guiWins[1]->numButt=0;
	
	L->guiWins[2]->win=newwin(16, 40, 16, 40);//info player 2
	addStr(L->guiWins[2]->label,"Information Player 2:","");
	L->guiWins[2]->numButt=0;
	
	L->guiWins[3]->win=newwin(7, 100, 32, 0);//Server options
	addStr(L->guiWins[3]->label,"Server:","");
	L->guiWins[3]->numButt=6;
	L->guiWins[3]->posButt=(int **)malloc(L->guiWins[3]->numButt*sizeof(int*));
	L->guiWins[3]->labButt=(char **)malloc(L->guiWins[3]->numButt*sizeof(char*));
	for(i=0;i<L->guiWins[3]->numButt;i++){
		L->guiWins[3]->posButt[i]=(int *)malloc(2*sizeof(int));
		L->guiWins[3]->labButt[i]=(char *)malloc(20*sizeof(char));
	}
	L->guiWins[3]->posButt[0][0]=3;
	L->guiWins[3]->posButt[0][1]=1;
	addStr(L->guiWins[3]->labButt[0],"Player","");
	L->guiWins[3]->posButt[1][0]=3;
	L->guiWins[3]->posButt[1][1]=23;
	addStr(L->guiWins[3]->labButt[1],"Server","");
	L->guiWins[3]->posButt[2][0]=3;
	L->guiWins[3]->posButt[2][1]=57;
	addStr(L->guiWins[3]->labButt[2],"timeOut","");
	L->guiWins[3]->posButt[3][0]=3;
	L->guiWins[3]->posButt[3][1]=72;
	addStr(L->guiWins[3]->labButt[3],"Port","");
	L->guiWins[3]->posButt[4][0]=3;
	L->guiWins[3]->posButt[4][1]=86;
	addStr(L->guiWins[3]->labButt[4],"Connect","");
	L->guiWins[3]->posButt[5][0]=3;
	L->guiWins[3]->posButt[5][1]=95;
	addStr(L->guiWins[3]->labButt[5],"OO","");
	
	L->guiWins[4]->win=newwin(7, 40, 25, 0);//Commands options
	addStr(L->guiWins[4]->label,"Commands:","");
	L->guiWins[4]->numButt=7;
	L->guiWins[4]->posButt=(int **)malloc(L->guiWins[4]->numButt*sizeof(int*));
	L->guiWins[4]->labButt=(char **)malloc(L->guiWins[4]->numButt*sizeof(char*));
	for(i=0;i<L->guiWins[4]->numButt;i++){
		L->guiWins[4]->posButt[i]=(int *)malloc(2*sizeof(int));
		L->guiWins[4]->labButt[i]=(char *)malloc(20*sizeof(char));
	}
	L->guiWins[4]->posButt[0][0]=3;
	L->guiWins[4]->posButt[0][1]=1;
	addStr(L->guiWins[4]->labButt[0]," < ","");
	L->guiWins[4]->posButt[1][0]=3;
	L->guiWins[4]->posButt[1][1]=6;
	addStr(L->guiWins[4]->labButt[1]," ^ ","");
	L->guiWins[4]->posButt[2][0]=3;
	L->guiWins[4]->posButt[2][1]=11;
	addStr(L->guiWins[4]->labButt[2]," v ","");
	L->guiWins[4]->posButt[3][0]=3;
	L->guiWins[4]->posButt[3][1]=16;
	addStr(L->guiWins[4]->labButt[3]," > ","");
	L->guiWins[4]->posButt[4][0]=3;
	L->guiWins[4]->posButt[4][1]=21;
	addStr(L->guiWins[4]->labButt[4],"Map Move","");
	L->guiWins[4]->posButt[5][0]=3;
	L->guiWins[4]->posButt[5][1]=31;
	addStr(L->guiWins[4]->labButt[5],"OK","");
	L->guiWins[4]->posButt[6][0]=3;
	L->guiWins[4]->posButt[6][1]=35;
	addStr(L->guiWins[4]->labButt[6],"XX","");
	
	L->guiWins[5]->win=newwin(32, 10, 0, 80);//Player mode
	addStr(L->guiWins[5]->label,"P.mode:","");
	L->guiWins[5]->numButt=7;
	L->guiWins[5]->posButt=(int **)malloc(L->guiWins[5]->numButt*sizeof(int*));
	L->guiWins[5]->labButt=(char **)malloc(L->guiWins[5]->numButt*sizeof(char*));
	for(i=0;i<L->guiWins[5]->numButt;i++){
		L->guiWins[5]->posButt[i]=(int *)malloc(2*sizeof(int));
		L->guiWins[5]->labButt[i]=(char *)malloc(20*sizeof(char));
	}
	L->guiWins[5]->posButt[0][0]=3;
	L->guiWins[5]->posButt[0][1]=1;
	addStr(L->guiWins[5]->labButt[0]," Dumb ","");
	L->guiWins[5]->posButt[1][0]=6;
	L->guiWins[5]->posButt[1][1]=1;
	addStr(L->guiWins[5]->labButt[1],"Manual","");
	L->guiWins[5]->posButt[2][0]=9;
	L->guiWins[5]->posButt[2][1]=1;
	addStr(L->guiWins[5]->labButt[2],"Random","");
	L->guiWins[5]->posButt[3][0]=12;
	L->guiWins[5]->posButt[3][1]=1;
	addStr(L->guiWins[5]->labButt[3],"  A*  ","");
	L->guiWins[5]->posButt[4][0]=15;
	L->guiWins[5]->posButt[4][1]=1;
	addStr(L->guiWins[5]->labButt[4],"Clever","");
	L->guiWins[5]->posButt[5][0]=18;
	L->guiWins[5]->posButt[5][1]=1;
	addStr(L->guiWins[5]->labButt[5],"XXXXXX","");
	L->guiWins[5]->posButt[6][0]=21;
	L->guiWins[5]->posButt[6][1]=1;
	addStr(L->guiWins[5]->labButt[6],"XXXXXX","");
	
	
	L->guiWins[6]->win=newwin(32, 11, 0, 90);//Opponent mode
	addStr(L->guiWins[6]->label,"Op.md:","");
	L->guiWins[6]->numButt=7;
	L->guiWins[6]->posButt=(int **)malloc(L->guiWins[6]->numButt*sizeof(int*));
	L->guiWins[6]->labButt=(char **)malloc(L->guiWins[6]->numButt*sizeof(char*));
	for(i=0;i<L->guiWins[6]->numButt;i++){
		L->guiWins[6]->posButt[i]=(int *)malloc(2*sizeof(int));
		L->guiWins[6]->labButt[i]=(char *)malloc(20*sizeof(char));
	}
	L->guiWins[6]->posButt[0][0]=3;
	L->guiWins[6]->posButt[0][1]=1;
	addStr(L->guiWins[6]->labButt[0]," Dumb  ","");
	L->guiWins[6]->posButt[1][0]=6;
	L->guiWins[6]->posButt[1][1]=1;
	addStr(L->guiWins[6]->labButt[1],"Manual ","");
	L->guiWins[6]->posButt[2][0]=9;
	L->guiWins[6]->posButt[2][1]=1;
	addStr(L->guiWins[6]->labButt[2],"Rand P ","");
	L->guiWins[6]->posButt[3][0]=12;
	L->guiWins[6]->posButt[3][1]=1;
	addStr(L->guiWins[6]->labButt[3],"Rand MP","");
	L->guiWins[6]->posButt[4][0]=15;
	L->guiWins[6]->posButt[4][1]=1;
	addStr(L->guiWins[6]->labButt[4],"   A*  ","");
	L->guiWins[6]->posButt[5][0]=18;
	L->guiWins[6]->posButt[5][1]=1;
	addStr(L->guiWins[6]->labButt[5]," MATCH ","");
	L->guiWins[6]->posButt[6][0]=21;
	L->guiWins[6]->posButt[6][1]=1;
	addStr(L->guiWins[6]->labButt[6],"CONTEST","");
	
	
	
	
	
		
	
	for(i = 0; i < nbrW; ++i)
	{
		showWin(L->guiWins[i]);
		L->panels[i] = new_panel(L->guiWins[i]->win);/* Attach a panel to each window */ 
		set_panel_userptr(L->panels[i%2], L->panels[(i+1)%2]);/* Set up the user pointers to the next panel */
	}
	
	
	update_panels();
	doupdate();
}

int GUI(Map *L,int lstGUIch)
{
	
	
	int c=0,i=lstGUIch/10;
	
	while(c!=-1)
	{
		dispMap(L);
		dispInfo(L);
		
		c=choice(L->guiWins[i],lstGUIch%10);
		//mvprintw(40, 0, "%d", c+i*10);
		if(c==9)
		{
			//top = (PANEL *)panel_userptr(top);
			//top_panel(top);
			lstGUIch=10;
			if(i==6)
				i=3;
			else
				i++;
		}
		int u=c+i*10;
		if(c!=-1&&c!=9)//if it's choice (not a change of win or a prg quit)
			return u;
		
	}
	
	
	update_panels();
	doupdate();
	getch();			/* Wait for user input */
	endwin();
	return -1;
}

int dispMap(Map* L)//Display the labyrinth
{
	//mvwprintw(win->win, 5,5, "%s", L->cases[0]);
	Win* win=L->guiWins[0];
	int starty=12-L->heigth/2,startx=18-L->width/2;
	mvwaddch(win->win, starty, startx, ACS_ULCORNER); 
	//mvwaddch(win->win, starty+1, startx, ACS_VLINE); 
	mvwvline(win->win, starty+1, startx, ACS_VLINE, L->heigth+1);
	mvwhline(win->win, starty, startx+1, ACS_HLINE, L->width); 
	mvwaddch(win->win, starty, startx+L->width+1, ACS_URCORNER); 
	mvwvline(win->win, starty+1, startx+L->width+1, ACS_VLINE, L->heigth+1);
	//mvwaddch(win->win, starty+1, startx+L->width+1, ACS_VLINE);
	mvwaddch(win->win, starty+L->heigth+1, startx+L->width+1, ACS_LRCORNER);
	mvwhline(win->win, starty+L->heigth+1, startx+1, ACS_HLINE, L->width); 
	mvwaddch(win->win, starty+L->heigth+1, startx, ACS_LLCORNER);
	
	int i,j;
	for(i=0;i<L->heigth;i++)
	{
		for(j=0;j<L->width;j++)
		{
			if(i==L->mvL||j==L->mvC)
				wattron(win->win, A_REVERSE); 
				
			switch(L->cases[i][j])
			{
				case 0:
					mvwaddch(win->win, starty+i+1, startx+j+1, ' ');
				break;
				case 1:
					mvwaddch(win->win, starty+i+1, startx+j+1, ACS_CKBOARD);
				break;
				case 2:
					wattron(win->win,COLOR_PAIR(3));
					mvwaddch(win->win, starty+i+1, startx+j+1, 'o');
					wattroff(win->win,COLOR_PAIR(3));
				break;
				case 3:
					wattron(win->win,COLOR_PAIR(1));
					mvwaddch(win->win, starty+i+1, startx+j+1, 'o');
					wattroff(win->win,COLOR_PAIR(1));
				break;
				case 4:
					wattron(win->win,COLOR_PAIR(4));
					//mvwprintw(win->win, starty+i+1, startx+j+1, "%s", "o");
					mvwaddch(win->win, starty+i+1, startx+j+1, 'o');
					wattroff(win->win,COLOR_PAIR(4));
				break;
				default:
					mvwaddch(win->win, starty+i+1, startx+j+1, L->cases[i][j]);
				break;
			}
			if(i==L->mvL||j==L->mvC)
				wattroff(win->win, A_REVERSE);
		}
	}
	update_panels();
	doupdate();
	return 1;
}

int dispPath(Map* L)//Display the path of a player
{
	int i,n=0;
	Win* win=L->guiWins[0];
	int starty=12-L->heigth/2+1,startx=18-L->width/2+1;
	Node * Nact;
	for(i=0;i<2;i++)
	{
		if(L->players[i]->toGoal!=NULL)//if a path has been calculated
		{
			Nact=L->players[i]->toGoal->first;
			while(Nact!=NULL)
			{
				if(n>1)
				{
					wattron(win->win,COLOR_PAIR(5+i));
					mvwaddch(win->win, starty+Nact->Y, startx+Nact->X, 'o');
					wattroff(win->win,COLOR_PAIR(5+i));
				}
				n++;	
				Nact=Nact->pathChild;
			}
		}
	}
	return 1;
}
int eraseMap(Map *L)
{
	Win* win=L->guiWins[0];
	int starty=12-L->heigth/2,startx=18-L->width/2;
	int i,j;
	for(i=0;i<L->heigth+2;i++)
		for(j=0;j<L->width+2;j++)
			mvwaddch(win->win, starty+i, startx+j, ' ');
			
	update_panels();
	doupdate();
	return 1;
}



void showWin(Win *win)
{	
	int height=0, width,i;	
	height++;
	//getbegyx(win->win, starty, startx);
	getmaxyx(win->win, height, width);

	box(win->win, 0, 0);
	mvwaddch(win->win, 2, 0, ACS_LTEE); 
	mvwhline(win->win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win->win, 2, width - 1, ACS_RTEE); 
	mvwprintw(win->win, 1, 2, "%s", win->label);
	//buttons
	for(i =0;i<win->numButt;i++)
	{
		wboxe(win, win->posButt[i][0], win->posButt[i][1], win->labButt[i]);
	}
}



void wboxe(Win *win, int starty, int startx,const char *string)
{
	mvwaddch(win->win, starty, startx, ACS_ULCORNER); 
	mvwaddch(win->win, starty+1, startx, ACS_VLINE); 
	mvwhline(win->win, starty, startx+1, ACS_HLINE, strlen(string)); 
	mvwaddch(win->win, starty, startx+strlen(string)+1, ACS_URCORNER); 
	mvwaddch(win->win, starty+1, startx+strlen(string)+1, ACS_VLINE);
	mvwaddch(win->win, starty+2, startx+strlen(string)+1, ACS_LRCORNER);
	mvwhline(win->win, starty+2, startx+1, ACS_HLINE, strlen(string)); 
	mvwaddch(win->win, starty+2, startx, ACS_LLCORNER);
	mvwprintw(win->win, starty+1, startx+1, "%s", string);	
	
}

int choice(Win *win,int lstCh)
{
	int ch=0,i;
	int highlight=lstCh;
	bool selected=false;
	
	while(ch!= 10 && ch != 'q' &&selected!=true)
	{
		for(i =0;i<win->numButt;i++)
		{
			if(highlight == i) /* High light the present choice */
			{	
				wattron(win->win, A_REVERSE); 
				mvwprintw(win->win, win->posButt[i][0]+1, win->posButt[i][1]+1, "%s", win->labButt[i]);
				wattroff(win->win, A_REVERSE);
			}
			else
				mvwprintw(win->win, win->posButt[i][0]+1, win->posButt[i][1]+1, "%s", win->labButt[i]);
		}
		update_panels();
		doupdate();
		ch = getch();
		switch(ch)
		{	case KEY_LEFT:
				if(highlight == 0)
					highlight = win->numButt-1;
				else
					--highlight;
				break;
			case KEY_RIGHT:
				if(highlight == win->numButt-1)
					highlight = 0;
				else 
					++highlight;
				break;
			case KEY_UP:
				if(highlight == 0)
					highlight = win->numButt-1;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == win->numButt-1)
					highlight = 0;
				else 
					++highlight;
				break;
			case 10:
				selected=true;
				
				break;
			case 'q':
				
				return (int)-1;
				break;
			case 9:
				mvwprintw(win->win, win->posButt[highlight][0]+1, win->posButt[highlight][1]+1, "%s", win->labButt[highlight]);
				return (int)9;
				break;
			default:
				mvprintw(0, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", ch, ch);
				//update_panels();
				break;
		}
		
		
	}
	
	return highlight;
}



int dispInfo(Map *L)//Display the Player info
{			
	Win* win1=L->guiWins[1];
	Win* win2=L->guiWins[2];
	int starty=3,startx=1;
	int i;
	mvwprintw(win1->win, starty, startx, "%s", "Name:");
	wattron(win1->win,COLOR_PAIR(3));
	mvwprintw(win1->win, starty, startx+5, "%s", L->infoP1[0]);
	wattroff(win1->win,COLOR_PAIR(3));
	mvwprintw(win1->win, starty+1, startx, "%s", "Energy:          ");
	mvwprintw(win1->win, starty+1, startx+7, "%s", L->infoP1[1]);
	mvwprintw(win1->win, starty+2, startx, "%s", "Infos:");
	for(i=3;i<10;i++)
		mvwprintw(win1->win, starty+i, startx, "%s", L->infoP1[i]);
		
	mvwprintw(win2->win, starty, startx, "%s", "Name:");
	wattron(win2->win,COLOR_PAIR(1));
	mvwprintw(win2->win, starty, startx+5, "%s", L->infoP2[0]);
	wattroff(win2->win,COLOR_PAIR(1));
	mvwprintw(win2->win, starty+1, startx, "%s", "Energy:          ");
	mvwprintw(win2->win, starty+1, startx+7, "%s", L->infoP2[1]);
	mvwprintw(win2->win, starty+2, startx, "%s", "Infos:");
	for(i=3;i<10;i++)
		mvwprintw(win2->win, starty+i, startx, "%s", L->infoP2[i]);
		
	update_panels();
	doupdate();	
	return 1;
}

char* selectL(Map *L, int w, int starty, int startx,char ** list)
{
	Win *win=L->guiWins[w];
	int x, y,highlight=0,ch=0,i;
	getbegyx(win->win, y, x);
	x+=startx;
	y+=starty;
	char label[50];
	int sizeL=0;
	while(list[sizeL]!=NULL){sizeL++;}//count the number of item to display
	
  	Win* directory = (Win *)malloc(sizeof(Win));
  	directory->win=newwin(sizeL+4,addStr(label,list[0],"")+6,y,x);
  	addStr(directory->label,"choose","");
  	directory->numButt=0;
  	
  	for(i=0;i<sizeL;i++) 
		mvwprintw(directory->win, 3+i, 2, list[i]);
  	
	showWin(directory);
	L->panels[nbrW] = new_panel(directory->win);
	top_panel(L->panels[nbrW]);
	update_panels();
	doupdate();
  	
	while(ch != 10)
	{	
		for(i =0;i<sizeL;i++)
		{
			if(highlight == i)
			{	
				wattron(directory->win, A_REVERSE); 
				mvwprintw(directory->win, 3+i, 2, "%s", list[i]);
				wattroff(directory->win, A_REVERSE);
			}
			else
				mvwprintw(directory->win, 3+i, 2, "%s", list[i]);
		}
		update_panels();
		doupdate();
		ch = getch();
		switch(ch)
		{	
			case KEY_LEFT:
				if(highlight == 0)
					highlight = sizeL-1;
				else
					--highlight;
				break;
			case KEY_RIGHT:
				if(highlight == sizeL-1)
					highlight = 0;
				else 
					++highlight;
				break;
			case KEY_UP:
				if(highlight == 0)
					highlight = sizeL-1;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == sizeL-1)
					highlight = 0;
				else 
					++highlight;
				break;
		}
	}
	wclear(directory->win);
	L->panels[nbrW] = NULL;
	for(i=0;i<nbrW;i++)
		top_panel(L->panels[i]);

	mvwprintw(win->win, starty+1, startx+1, "%s", list[highlight]);
	update_panels();
	doupdate();
	  
	return list[highlight];
	  
	
			
}

