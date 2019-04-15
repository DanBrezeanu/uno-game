#!/bib/sh

CC=gcc
CFLAGS= -std=gnu99 -Wall -Wno-implicit-function-declaration
EXEC=uno
LIBS=-lncursesw

build: uno.o miscellaneous.o AI_functions.o draw_functions.o game_logic.o
	$(CC) $^ $(CFLAGS) -o $(EXEC) $(LIBS)

uno.o: uno.c
	$(CC) $^ $(CFLAGS) -c

miscellaneous.o: miscellaneous.c
	$(CC) $^ $(CFLAGS) -c

AI_functions.o: AI_functions.c
	$(CC) $^ $(CFLAGS) -c

draw_functions.o: draw_functions.c
	$(CC) $^ $(CFLAGS) -c

game_logic.o: game_logic.c
	$(CC) $^ $(CFLAGS) -c

run:
	./$(EXEC)

zip:
	zip uno-game.zip *.c *.h README MAKEFILE\ OPTIONS

clean:
	rm -rf $(EXEC) uno.o miscellaneous.o AI_functions.o draw_functions.o game_logic.o
