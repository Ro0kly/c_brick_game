TETRIS_FILE=brick_game/tetris/tetris.c
DRAW_FILE=gui/cli/draw.c
DATA_FILE=data/tetrominos.c
t:
	gcc main.c ${DATA_FILE} ${TETRIS_FILE} -o program.out -lncurses
	./program.out
g:
	gcc main.c ${DATA_FILE} ${TETRIS_FILE} ${DRAW_FILE} -o program.out -lncurses
	./program.out
