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
EXEC3=pnm_test
EXEC4=codebarre_test
DOXYGEN=doxygen
MODULES_PNM=main-pnm.c pnm.c
OBJETS_PNM=main-pnm.o pnm.o
MODULES_CODEBARRE=main-codebarre.c codebarre.c pnm.c
OBJETS_CODEBARRE=main-codebarre.o codebarre.o pnm.o
OBJETS_PNM_TEST= seatest.c pnm.c pnm_test.c
MODULES_PNM_TEST= seatest.o pnm.o pnm_test.o
MODULES_CODEBARRE_TEST = seatest.c pnm.c codebarre_test.c codebarre.c
OBJETS_CODEBARRE_TEST = seatest.o pnm.o codebarre_test.o codebarre.o
## Rules

all: pnm codebarre pnm_test  codebarre_test

codebarre: $(OBJETS_CODEBARRE)
	$(LD) -o $(EXEC2) $(OBJETS_CODEBARRE) -lm $(LDFLAGS)

codebarre_test:$(OBJETS_CODEBARRE_TEST)
	$(LD) -o $(EXEC4) $(OBJETS_CODEBARRE_TEST) $(LDFLAGS)

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

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

pnm_test:$(OBJETS_PNM_TEST)
	$(LD) -o $(EXEC3) $(OBJETS_PNM_TEST) $(LDFLAGS)

pnm_test.o:pnm_test.c
	$(CC) -c $(MODULES_PNM_TEST) -o pnm_test.o $(CFLAGS)

codebarre_test:codebarre_test.o
	$(LD) -o $(EXEC4) $(OBJETS_CODEBARRE_TEST) $(LDFLAGS)

codebarre_test.o:codebarre_test.c
	$(CC) -c $(MODULES_CODEBARRE_TEST) -o codebarre_test.o $(CFLAGS)

doc:
	$(DOXYGEN) Doxyfile

#test:
	#$(EXEC4)

clean:
	rm -f *.o $(EXEC1) $(EXEC2) $(EXEC3) *~
	rm -r html
