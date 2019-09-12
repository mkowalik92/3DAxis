CMNDIR=./common/
EXTDIR=./external/
CC=gcc
CFLAGS=-ldl -lglfw -I$(CMNDIR)
LIBS=$(EXTDIR)glad.c $(CMNDIR)window.c

OBJ=main.c $(CMNDIR)window.c $(CMNDIR)window.h $(CMNDIR)shader.h

crun: $(OBJ)
	$(CC) main.c $(LIBS) $(CFLAGS)
	./a.out

run :
	./a.out

clean :
	rm ./a.out
