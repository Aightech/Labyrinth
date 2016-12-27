# Modèle de fichier Makefile  pour le fichier template.c
LIBDIR = /home/sasl/encad/brajard/projet/CGS_lib

# options de compilation
CC =gcc
CCFLAGS = -Wall -Wno-switch -I $(LIBDIR)/include
LIBS = -L $(LIBDIR)/lib
LDFLAGS = -lm -lcgs -lncurses -lpanel

# fichiers du projet
SRC = main.c gui.c mapping.c dumbMd.c manualMd.c randMd.c astarMd.c
OBJ = $(SRC:.c=.o)
EXEC = test


# règle initiale
all: $(EXEC) clean

# dépendance des .h
main.o: gui.h mapping.h struct.h dumbMd.h astarMd.h
gui.o: gui.h struct.h mapping.h
mapping.o:gui.h struct.h mapping.h
mapping.o:gui.h struct.h dumbMd.h mapping.h
manualMd.o:gui.h struct.h manualMd.h mapping.h
randMd.o:gui.h struct.h randMd.h mapping.h
astarMd.o:gui.h struct.h astarMd.h mapping.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# règles supplémentaires
clean:
	@rm -rf *.o
rmproper:
	rm -rf $(EXEC) *.o
