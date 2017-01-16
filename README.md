# Labyrinth
[ROB3] Labyrinth Game

##list of structures:
**LStep** *A case to move at or a modification of the map*

**Node**  *A node of the map (useful for Astar search)*

**Path**  *list of step and its size*

**Player** *player*

**Map** *the labyrinther*

##list of functions:
###GUI functions 
**int GUI(Map* L,int lastCh);** *Monitor the gui system and all other graphical functions*

**int dispMap(Map* L);** *Display the labyrinth*

**int dispInfo(Map* L);** *Display players' information*

**int dispPath(Map* L);** *Display the paths of the players to the goal*

###Map functions 

**Map* initMap();** *Initialize the map*

**void getMap(Map *L);** *get the map from the server*
###Movements functions 
**int testMoveP(Map L, Player P,char move);** *Return 1. If can't move return : -1(wall) -2(player)* 

**int move(Map L, Player P,char move);** *Return 1. If can't move return : -1(wall) -2(player)*

**int moveMap(Map L,int row, int line);** *Return 1. If can't move return : -1(not enought energy)*

**Path Astar(Map L,Player P1, Player P2);** *Return the shortest path beetween P1 and P2 (could work with Map move)*

**int evaluate(Map L);**
