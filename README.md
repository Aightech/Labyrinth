#DONJON ET JAMBON


INTRODUCTION: 

Kidnappé, affamé pendant 40 jours et laché dans une microplanète en forme de labyrinthe. 
Votre seul espoir de survie ? Une tranche de jambon, cachée quelque part dans ce labyrinthe.
Cependant, vos kidnappeurs vous ont expliqué qu'une autre personne est également présente dans le labyrinthe, et elle aussi a faim.
Parviendrez-vous à atteindre en premier votre salut ?
Utilisez de manière astucieuse les murs amovibles  de ce jeu au tour par tour révolutionnaire pour laisser vos adversaires mourrir de faim !
Affrontez vos amis dans un mode deux joueurs d'un réalisme à couper le souffle !
Et surtout n'oubliez pas : le jambon, c'est pour les bons !



                                            8,:::.                              
                                           8:,,,:,   ..                         
                                           ,,,,,:,O~Z:,,,,8                   
                                           8,,,,:,,~,,,,,,,8                   
                                            .,,,,~,,,,,,,,,8               
                                             8,,,.,,,,,,,,,.                   
                                            .,,,,,:8,,,,,,.                     
                                           ,,,,,:.     ..                       
                                        .8,,,,,..                               
                                     .ZZ777Z8.,.                                
                                   .ZZZOZZZZ7Z8                                 
                                 ,ZZZ8ZZ+ZZZZZZ                                 
                               8ZZ8ZZZZZZZZZ$Z8                                 
                            7$ZZZZZ$ZZZZZZZZ7Z.                                 
                         .8ZZZ8ZZZZZZZZZZZZZ78                                  
                        .Z7Z8ZZZZZZZZZZ7ZZ8Z78                                  
                      .O$$8ZZIZZZZZ8ZZ7ZZZ8ZZ8                             
                    .OZ78ZZZZIZZZZ8ZZ7ZZZ8Z$Z~                           
                 .8ZZ7$ZZZIIIZZZZ8ZZ7ZZZZOZ7Z.                                 
             .IZZ777ZZZZIIZZZZZZZZZZ7ZZZ8ZZ7Z.                                  
           8ZZ7ZZZZZZZZZZ$ZZZZZO$ZZ7ZZZZZZZZ8                                   
       .8ZZZ77ZZZZZZZZZZZZZZZZZZZZ7ZZZZ8ZZZZ                                    
     ,ZZ77ZZZZ88===$8ZZZZZZZZZZZZ7ZZZZZZZZZO.                                   
   .ZZ7ZZ8=======+++====8ZZZZZZZZZZZZ$8ZZZZZ                                    
 .?Z7ZO==~~~=====+====++===OZZZZZZZZZZZZZZZ8                                    
 DZ7Z==~~=~=+++====::~===+===ZZZZZZZZZOZZZZ8                                    
.Z7Z==~=:==++=:+=========++===ZZZ7ZZ$ZOZZ7Z.                                    
ZZ7==~=~=++=:=========~~=======ZZZ7$ZZ8ZZ7Z                                     
ZZZ==~==++===+==~~~==:+=~==+====Z$Z7ZZ8ZZ$O                                     
ZZZ=~~==+=~+=~~=====~==:=~======ZZZ7Z$ZZ7Z.                                    
ZZ$8=~=?~===~~===========~=+=~~==ZZ$ZZZZ78                               , .    
ZZ7Z==~+==+=~===....8===:===~+~~=8ZZOZZ7Z                               . ...   
8ZZZ8+:++=+=~===..78.=~=:=~~~+:==ZZZZZ7Z............                   .:.,.,.  
.OIZZ===++=+=~===888====:=:=+=~==ZZ7Z78........:..................... .,.....   
 .8ZZZ+==++=+=~~~=======:=~=+=~==8Z$Z$........................................  
   7ZZ$O===++==========:=~~=+=~==I7Z$..............................    .........
    .OZZZZ==:=++++=++:==~~====~=8$Z7+.......................            .....   
      .8ZZZZZ=========~==~~==~=OZZZ8.................. .                        
        .,ZZZZZ8===::::====~==ZZZZ8...............                              
           .~ZZZZZ8+=======8ZZZZ8............ .                                 
              ...8OZZZZZZZZZZ8..........                                        
                  ........                                                      



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

**int moveP(Map L, Player P,char move);** *Return 1. If can't move return : -1(wall) -2(player)*

**int moveM(Map L,int row, int line);** *Return 1. If can't move return : -1(not enought energy)*

**Path Astar(Map L,Player P1, Player P2);** *Return the shortest path beetween P1 and P2 (could work with Map move)*


