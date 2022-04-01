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
RANLIB= ranlib
AR=ar
LDFLAGS=

# Files
EXEC1=pnm
EXEC2=codebarre
EXEC3=pnm_test
EXEC4=codebarre_test
EXEC5=libpnm.a
DOXYGEN=doxygen

OBJETS_PNM_TEST= seatest.o pnm.o pnm_test.o
OBJETS_CODEBARRE = main-codebarre.o codebarre.o
OBJETS_CODEBARRE_TEST= codebarre_test.o seatest.o pnm.o codebarre.o
OBJETS_LIBPNM=pnm.o
## Rules

all: codebarre  pnm_test
test: codebarre_test
lib: libpnm.a
doc:
	$(DOXYGEN) Doxyfile

libpnm.a:$(OBJETS_PNM)
	$(AR) ruv $@ $?
	$(RANLIB) $@

pnm_test:$(OBJETS_PNM_TEST)
	$(LD) -o $(EXEC3) $(OBJETS_PNM_TEST) $(LDFLAGS)

codebarre:$(OBJETS_CODEBARRE)
	$(LD) -o $(EXEC2) $(OBJETS_CODEBARRE) -lm $(LDFLAGS)

codebarre_test:$(OBJETS_CODEBARRE_TEST)
	$(LD) -o $(EXEC4) $(OBJETS_CODEBARRE_TEST) -lm $(LDFLAGS)

codebarre.o:codebarre.c
	$(CC) -c codebarre.c -L. -lpnm -o codebarre.o $(CFLAGS) -lm

main-codebarre.o:main-codebarre.c
	$(CC) -c main-codebarre.c -o main-codebarre.o $(CFLAGS)

codebarre_test.o:codebarre_test.c
	$(CC) -c codebarre_test.c -o codebarre_test.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

clean:
	rm -f *.a *.o *-copie.* $(EXEC1) $(EXEC3) $(EXEC2) $(EXEC4) *~
	rm -r html
