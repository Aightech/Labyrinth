#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "guilib.h"
#include "struct.h"
#include "strlib.h"

#include "mapping.h"
#include "dumbMd.h"
#include "manualMd.h"
#include "randMd.h"
#include "astarMd.h"

/*! \file main.c
    \brief Main file to run the different modes and GUI options.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

/*
  _____              _                    _       _                 _                 
 |  __ \            (_)                  | |     (_)               | |                
 | |  | | ___  _ __  _  ___  _ __     ___| |_     _  __ _ _ __ ___ | |__   ___  _ __  
 | |  | |/ _ \| '_ \| |/ _ \| '_ \   / _ \ __|   | |/ _` | '_ ` _ \| '_ \ / _ \| '_ \ 
 | |__| | (_) | | | | | (_) | | | | |  __/ |_    | | (_| | | | | | | |_) | (_) | | | |
 |_____/ \___/|_| |_| |\___/|_| |_|  \___|\__|   | |\__,_|_| |_| |_|_.__/ \___/|_| |_|
                   _/ |                         _/ |                                  
                  |__/                         |__/                                   

.  .                                                                            
...                                                                             
......                                                                          
.........                                                                       
... ......                                                                      
..........   .                                                                  
............                                                                    
...............                                                                 
...............                                                                 
....$?II~~,+ ...                                                                
.:ZZ$=+=~==?=$I+....                                                            
$$$$=$?II?I7II7II?I=+~...                                                       
$$$$$$?I7$777$77$$$?I?7,+?==,.:==+,+.,....  . ...  .                            
$$$$7$$$$7$$$7$O$7$~=I7,7++.?:.....I7+~~~,:..,::..,....                         
$$$$77$$$$$?7II+77$II~=,+~~~~,++=+I=+I,??:::I~.+~??,~:,.......                  
77$$$77$$$$$I?+==7$$7I+?=:~=$??~I+~?,+?Z:~=+7Z77~=I=~~.+=:,~..,...              
7$77$7$$$7$$+7?,,7=I$$II?7?$7?~?=+?+$I?=?7+?I+=+++I==I??$7~~?~+=,,..            
.$$$7$$$?ZZ$$$$777+7==II$=?I=?+~I+7~~=~~$~II7777I?$Z$OZ$I77$I~.,,:.~=,.         
.$$$$$$$$$$$$?$$I$=+??=+?I??=II=??+II+?I+I7?7?~I$$$7$7$$~=+?I==?~=~.:+,+.      .
..Z$$$I=$$ZZZ$$$7$7$?=I+++?I+=III7?II7$77I++=I7I$Z7777:+?~7777I7I??=+,:+?I. ... 
....$$7$$$ZZZZZ$?+I?I+$I=?7+?+777I?+$$II+?$7??~ZI$=::+77++=?II?=,~??=~,7I?$? ...
....,7$Z7?$$Z$$$?~~+==?I77I+7+II7I$I7??7$7II+7777$I+7+7?I+$7I?~==~7+++====+IO...
.....,:Z$=$$$Z$$77I?++??77??I+$I7?I?=II$7777777I?7$7~?+I$7II7$?++====~~~~===?$..
....,,,::~$$Z7$?++?=+?I?I?=++I+?7I77I~+,:,~I?~++=I?I7I?=.Z?++===~=~=~=~~=====?,.
..,,,,:~~=I$$$777?I??+$=?=?+II+??$+~++7=+:=I=?~=~?=~~$+++==~~~~~~~~~~~~=======..
,,,,:~~~==7$$$777I?7???==?+++???++???IIII:?:,?I~+7+===~==~~~~~~~~$ZZIZ~~~=====..
,,::~~~~~~7$$77$$777$II???+???+7I+==+++?+===7+========~~~~ZZZ$Z$ZZ7ZZZZ7~~=~=+..
,,:~~~~~~~7$$$$$$$77$$II7I?+I=??I?+III~7++======~=~~~~ZZZ$$7OZZZ$ZZZZZZ$=~===+..
,::~~~~~~+I$$$$$$777$7$77III???I??+I===========~~~~=ZZZZZOZ$ZZ7ZZZZZZZZZZ~=+I+..
::~~~~~~~+77$$$$7777777777I7$$7I+===========~~=~IZ$ZZ$ZZ$OZZZZOZZOOOZZZZZ++Z$7..
:::~~~~~~I77$$7777777777777?7I=====~==7O=====+7$7ZZOZZOZZZZZ$ZZZIIIZZOZZOZ?ZZ...
::~~~~~~~:II7777777=7777777?+=+=~~=ZZZZOOZOZOO?=+ZZZZOOOOZ$OZOOOOO$OOOOOOZZO....
:::~~~~~~~I??77777I7IIIII?+++=~~==ZZZZZZOOZZOOOOO+OZOZOZ$OZOOZOOOZOOOOOO$?$Z..,,
,::~~~~~~~7?I?II?I?+????I++==~?==ZZZZZZOOOOOO8OOOO===OOOOOOZOOOOOOO?++O?77:,,,:,
,::::~~~~~7I?I?+???II=??++=~OZ+=$ZZZZZOOOOO8OZZO8O8Z+++ZOOOO$?I$OOOI?7$=:,,,,,,:
,,::::~~~~77?I7II??I+==++==ZZ=ZZZZZ7OZZOOOOO8OO8OO8$I?ZOZ?+OOO888OZ7$7?~:,,,,,..
,,,:::::~~~$7?=7II?II+?==+OZ+OZZIOOOZOOOO$Z8O8OO888O8IOOZOZ88O888Z$$I?+~:,,.....
,,,,:::::::777I7IIII+?I=?ZO+ZZZZZOOOOOOOO8OZOOO888OO88Z+~?O8$Z$$$7I??=~::,......
.,,,,,:::::~77III??III++Z$Z?ZZZZOOOOOOO888888I8888OOOMNDDOZ$$77I?+=~~:::,,..,...
,,,,,,,:::::~I77III????+ZOO?ZOOZOOOOOOO8888DD878$ZOZZ$$$$7II?+=~~:::::,,,,......
....,,,,,::::=I77III????=$O$$ZZZZOOOO88O8DDNDDZO8$$777I?++=~~::::::,,,,,,,,.....
......,,,,::::=7$7I7I???==~ZOOZOOOOO88888DDDDDZ$777I+=~~:::::::,,,,,,,,,,,,.....
.......,,,::::~=77IIIII?+=~=7$OOO888888DDD8D$$77?+=~::::::,,,,,,,,,,,,,,,,,.....
.........,,,::::=?$II77I?+==~=IZ888DDD8$DZ$7I+~:::::::,,,,,,,,,,,,,,,,,,,,,.....
...........,,,:::~=+I$?II?++===7OO8887$$I+~:::,:,,,,,,,,,,,,,,,,,,,,,,,,,,,.....
.............,,,,,,:~~+?7$I+??IZOZ$7I=:::,,,,,,,,,,,,,,......,..,.,,,,,,,,,.....
...................,,,,:~=++??++=~::,,,,,,,,,,.,.................,,,,,,,,.......
............................,..,..,............................,,.,,,,,.........
... ....................................................,............,.,........
..... ...........................................................,..............

*/


extern int debug;


int main()
{
	debug=0;
	Map *L=initMap();
	initGUI(L);
	//t_move* move=(t_move*) malloc(sizeof(t_move));
	
	int choice=53,i;
	
	addStr(L->infoP1[5]," Select your mode.","");
	while(choice!=-1)
	{	
		dispInfo(L);
		choice=GUI(L,choice);
		switch(choice)
		{
			case 30:
				addStr(L->PlayerName,selectL(L,3,L->guiWins[3]->posButt[0][0],L->guiWins[3]->posButt[0][1]+8,L->listPlrName),"");
				choice++;
			break;
			case 31:
				addStr(L->ServerName,selectL(L,3,L->guiWins[3]->posButt[1][0],L->guiWins[3]->posButt[1][1]+8,L->listSvrName),"");
				choice++;
			break;
			case 32:
				addStr(L->TimeOut," timeout=",selectL(L,3,L->guiWins[3]->posButt[2][0],L->guiWins[3]->posButt[2][1]+9,L->listTimeOut));
				choice++;
			break;
			case 33:
				addStr(L->PortName,selectL(L,3,L->guiWins[3]->posButt[3][0],L->guiWins[3]->posButt[3][1]+7,L->listPrtName),"");
				choice++;
			break;
			case 34://connection to the server
				
				addStr(L->infoP1[5],"                                     ","");
				getMap(L);//switch of the value getmap return to lauched the game mode
				if(L->players[0]->mode==0)//we are dumb
					dumbMode(L);
				else if(L->players[0]->mode==1)//we play manual
					manualMode(L);
				else if(L->players[0]->mode==2)//we play random
					randMode(L);
				else if(L->players[0]->mode==3)//we play astar
					astarMode(L);
			
				for(i=3;i<7;i++)
				{
					addStr(L->infoP1[i],"                                 ","");
					addStr(L->infoP2[i],"                                 ","");
				}
				addStr(L->infoP1[5]," Select your mode.","");
				freeMap(L);
				choice=50;	
			break;
			case 35://connection to the server
				while(true){
					addStr(L->infoP1[5],"                                     ","");
					//freeMap(L);
					getMap(L);//switch of the value getmap return to lauched the game mode
					if(L->players[0]->mode==0)//we are dumb
						dumbMode(L);
					else if(L->players[0]->mode==1)//we play manual
						manualMode(L);
					else if(L->players[0]->mode==2)//we play random
						randMode(L);
					else if(L->players[0]->mode==3)//we play astar
						astarMode(L);
					/*Pause l'application pour i milliseconds*/
					clock_t start,end;
					start=clock();
					int i=50;
		    			while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));
		    			
				}
				for(i=3;i<7;i++)
				{
					addStr(L->infoP1[i],"                                 ","");
					addStr(L->infoP2[i],"                                 ","");
				}
				addStr(L->infoP1[5]," Select your mode.","");
				choice=50;	
			break;
			
			/*MANUAL MOVES
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
			break;*/
			
			/*PLAYER MODES*/
			case 50://DO NOTHING
			case 51://MANUAL
			case 52://RANDOM
			case 53://ASTAR
				L->players[0]->mode=choice%10;
				addStr(L->infoP1[5]," Select the mode of your opponent.","");
				choice+=10;
			break;
			
			/*OPONENT MODES*/
			case 60://DO NOTHING
			case 61://MANUAL
			case 62://RANDOM MOVEP
			case 63://RANDOM MOVEP&M
			case 64://ASTAR
			case 65://Match
			case 66://CONTEST
				L->players[1]->mode=choice%10;
				addStr(L->infoP1[5]," Select <ENTER> to get a map","");
				choice=30;
			break;
				
   
			
		}
	}
	//freeMap(L);
	freeGUI(L);
	return 0;
}



