# Modèle de fichier Makefile  pour le fichier template.c
LIBDIR = /home/sasl/encad/brajard/projet/CGS_lib

# options de compilation
CC =gcc
CCFLAGS = -Wall -Wno-switch -I $(LIBDIR)/include
LIBS = -L $(LIBDIR)/lib
LDFLAGS = -lm -lcgs -lncurses -lpanel

# fichiers du projet
SRC = main.c guilib.c mapping.c dumbMd.c manualMd.c randMd.c astarMd.c strlib.c
OBJ = $(SRC:.c=.o)
EXEC = test


# règle initiale
all: $(EXEC) clean

# dépendance des .h
main.o: guilib.h mapping.h struct.h dumbMd.h astarMd.h
guilib.o: guilib.h struct.h mapping.h
mapping.o:guilib.h struct.h mapping.h
dumbMd.o:guilib.h struct.h dumbMd.h mapping.h
manualMd.o:guilib.h struct.h manualMd.h mapping.h
randMd.o:guilib.h struct.h randMd.h mapping.h
astarMd.o:guilib.h struct.h astarMd.h mapping.h 

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
