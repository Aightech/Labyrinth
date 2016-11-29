# Modèle de fichier Makefile  pour le fichier template.c
LIBDIR = /home/sasl/encad/brajard/projet/CGS_lib

# options de compilation
CC =gcc
CCFLAGS = -Wall -I $(LIBDIR)/include
LIBS = -L $(LIBDIR)/lib
LDFLAGS = -lm -lcgs -lncurses -lpanel

# fichiers du projet
SRC = main.c gui.c mapping.c
OBJ = $(SRC:.c=.o)
EXEC = test


# règle initiale
all: $(EXEC)

# dépendance des .h
main.o: gui.h struct.h
gui.o: gui.h struct.h
mapping.o:gui.h struct.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# règles supplémentaires
clean:
	rm -f *.o
rmproper:
	rm -f $(EXEC) *.o
