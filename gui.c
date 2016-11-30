#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "struct.h"
#include "gui.h"
#define nbrW 5

int GUI(Map *L,int lstGUIch)
{
	initscr();
	clear();
	noecho();
	start_color();
	cbreak();	/* Line buffering disabled. pass on everything */
	keypad(stdscr, TRUE);
	refresh();
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	
	PANEL  *my_panels[nbrW];
	WIN my_wins[nbrW] = {{newwin(25, 40, 0, 0),"Map:",{},{},0},
				{newwin(14, 40, 0, 40),"Information Player 1:",{},{},0},
				{newwin(14, 40, 14, 40),"Information Player 2:",{},{},0},
				{newwin(28, 10, 0, 80),"Modes:",{"GetMap"," Dumb ","Manual"," Auto "," Stop "},{{3,1},{6,1},{9,1},{12,1},{15,1},{3,28}},5},
				{newwin(7, 40, 25, 0),"Commands:",{" < "," ^ "," v "," > ","Pause","Map Move"},{{3,1},{3,6},{3,11},{3,16},{3,21},{3,28}},6},
				};
				
	int i;
	for(i = 0; i < nbrW; ++i)
	{
		win_show(&my_wins[i]);
		my_panels[i] = new_panel(my_wins[i].win);/* Attach a panel to each window */ 
		set_panel_userptr(my_panels[i%2], my_panels[(i+1)%2]);/* Set up the user pointers to the next panel */
	}
	
	
	update_panels();
	doupdate();
	i=4;
	int c=0;
			
	//PANEL  *top;
	while(c!=-1)
	{
		dispMap(L,&my_wins[0]);
		c=choice(&my_wins[i],lstGUIch%10);
		//mvprintw(40, 0, "%d", c+i*10);
		if(c==9)
		{
			//top = (PANEL *)panel_userptr(top);
			//top_panel(top);
			if(i==4)
				i=3;
			else
				i++;
		}
		int u=c+i*10;
		switch(u)
		{	
			case 30:
				
				return u;
			break;
			
			case 40:
				return u;
			break;
			case 41:
				return u;
			break;
			case 42:
				return u;
			break;
			case 43:
				return u;
			break;
			
			
		}
	}
	
	
	update_panels();
	doupdate();
	getch();			/* Wait for user input */
	endwin();
	return -1;
}

int dispMap(Map* L,WIN* win)//Display the labyrinth
{
	//mvwprintw(win->win, 5,5, "%s", L->cases[0]);
	int starty=3,startx=1;
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
			//printf("(%d,%d)= ",i,j);
			if(L->cases[i][j]==1)
				mvwaddch(win->win, starty+i+1, startx+j+1, ACS_CKBOARD);
			else if(L->cases[i][j]==2)
			{
				wattron(win->win,COLOR_PAIR(3));
				//mvwprintw(win->win, starty+i+1, startx+j+1, "%s", "o");
				mvwaddch(win->win, starty+i+1, startx+j+1, 'o');
				wattroff(win->win,COLOR_PAIR(3));
			}
			//scanf("%d",&p[i][j]);
			//printf("(%d,%d)= %d\n",i,j,p[i][j]);
		}
	}
	
	return -1;
}

void win_show(WIN *win)
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
		boxe(win, win->posButt[i][0], win->posButt[i][1], win->buttLab[i]);
	}
}

void boxe(WIN *win, int starty, int startx,const char *string)
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

int choice(WIN *win,int lstCh)
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
				mvwprintw(win->win, win->posButt[i][0]+1, win->posButt[i][1]+1, "%s", win->buttLab[i]);
				wattroff(win->win, A_REVERSE);
			}
			else
				mvwprintw(win->win, win->posButt[i][0]+1, win->posButt[i][1]+1, "%s", win->buttLab[i]);
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
				mvwprintw(win->win, win->posButt[highlight][0]+1, win->posButt[highlight][1]+1, "%s", win->buttLab[highlight]);
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
