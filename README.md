# Labyrinth
[ROB3] Labyrinth Game

##list of structures:
**LStep**

**Path**  *list of lab case and its size*

**Player** *player*

**Map** *the labyrinther*

##list of functions:
**int dispMap(Map L);** *Display the labyrinth*

**void initMap(Map L);**

**void updateMap(Map L);**

**int move(Map L, Player P,char move);** *Return 1. If can't move return : -1(wall) -2(player)*

**int moveMap(Map L,int row, int line);** *Return 1. If can't move return : -1(not enought energy)*

**Path Astar(Map L,Player P1, Player P2);** *Return the shortest path beetween P1 and P2 (could work with Map move)*

**int evaluate(Map L);**
