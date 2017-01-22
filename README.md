#DONJON ET JAMBON


##INTRODUCTION: 

Kidnappé, affamé pendant 40 jours et laché dans une microplanète en forme de labyrinthe. 

Votre seul espoir de survie ? Une tranche de jambon, cachée quelque part dans ce labyrinthe.

Cependant, vos kidnappeurs vous ont expliqué qu'une autre personne est également présente dans le labyrinthe, et elle aussi a faim. Parviendrez-vous à atteindre en premier votre salut ?

Utilisez de manière astucieuse les murs amovibles  de ce jeu au tour par tour révolutionnaire pour laisser vos adversaires mourrir de faim !

Affrontez vos amis dans un mode deux joueurs d'un réalisme à couper le souffle !

Et surtout n'oubliez pas : le jambon, c'est pour les bons !

Mode Name | Specifications
------------ | -------------
Dumb | The player don't move.
Manual | You move the player by yourself.
Random | The player move randomly 
A* | The player will go to the goal following the shortest path of the current map.
Clever | Not available yet.

 A game produced by @BarbeBleue and @Aightech


                                     

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
**int testMoveP(Map L, Player P,char move);** *Return 0. If can't move return : -1(wall) . If you win: 1 

**int testMoveM(Map L, Player P);** *Return 0. If can't move return : -1(not enough enrgy) 

**int moveP(Map L, Player P,char move);** *Return 0. If can't move return : -1(wall) . If you win: 1 

**int moveM(Map L,int row, int line);** *Return 0. If can't move return : -1(not enought energy)*


