TETRIS_FILE=brick_game/tetris/tetris.c
DRAW_FILE=gui/cli/draw.c
DATA_FILE=data/tetrominos.c
ACTION_FILE=gui/cli/action.c
t:
	gcc main.c ${DATA_FILE} ${TETRIS_FILE} -o program.out -lncurses
	./program.out
g:
	gcc main.c ${DATA_FILE} ${TETRIS_FILE} ${DRAW_FILE} ${ACTION_FILE} -o program.out -lncurses
	./program.out
