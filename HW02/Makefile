CC = gcc
CFLAGS = -Wall -g

OBJ = search.o traverse.o display.o 

search: $(OBJ)
	gcc $(CFLAGS) -o search $(OBJ)

search.o: search.c traverse.h display.h
	gcc $(CFLAGS) -c search.c

traverse.o: traverse.c traverse.h display.h
	gcc $(CFLAGS) -c traverse.c

display.o: traverse.c display.h traverse.h
	gcc $(CFLAGS) -c display.c

clean:
	rm -f *.o search