CC=gcc
FLAGS=-Wall -Werror -Wextra
CURSES=-lncurses

LOGIC=brick_game/
UI=gui/cli/
EXE=tetris_exe

style=clang-format -style=Google

CLEANER=rm -rf

lite:
	$(CC) $(LOGIC)tetris.c $(UI)interface.c -o $(EXE) $(CURSES)
	./$(EXE)

hard:
	$(CC) $(FLAGS) $(LOGIC)tetris.c $(UI)interface.c -o $(EXE) $(CURSES)

clean:
	$(CLEANER) *.out *.o $(EXE)