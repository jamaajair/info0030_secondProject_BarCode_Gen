###
## Jamaa JAIR s207171
## INFO0030: Projet 2
##
###

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -lm
LD=gcc
LDFLAGS=

# Files
EXEC1=pnm
EXEC2=codebarre
DOXYGEN=doxygen
MODULES_PNM=main-pnm.c pnm.c
OBJETS_PNM=main-pnm.o pnm.o
MODULES_CODEBARRE=main-codebarre.c codebarre.c pnm.c
OBJETS_CODEBARRE=main-codebarre.o codebarre.o pnm.o
## Rules

all: pnm codebarre

codebarre: $(OBJETS_CODEBARRE)
	$(LD) -o $(EXEC2) $(OBJETS_CODEBARRE) -lm $(LDFLAGS)

codebarre.o: codebarre.c
	$(CC) -c codebarre.c -o codebarre.o $(CFLAGS)

main-codebarre.o: main-codebarre.c
	$(CC) -c main-codebarre.c -o main-codebarre.o $(CFLAGS)

pnm: $(OBJETS_PNM)
	$(LD) -o $(EXEC1) $(OBJETS_PNM) $(LDFLAGS)

main-pnm.o: main-pnm.c
	$(CC) -c main-pnm.c -o main-pnm.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

doc:
	$(DOXYGEN) Doxyfile

clean:
	rm -f *.o $(EXEC1) $(EXEC2) *~
	rm -r html
