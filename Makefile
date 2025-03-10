GCC=gcc
C_FLAGS=-std=c11 -Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
TARGET=program.out
DIST_TARGET=program.tar.gz
TEST_TARGET=tests.out
BIN_DIR=bin
DIST_DIR=dist
COVERAGE_DIR=coverage
COVERAGE_REPORT_DIR=report
TEST_DIR=tests
MAIN_FILE=src/main.c
TETRIS_FILE=src/brick_game/tetris/tetris.c
DRAW_FILE=src/gui/cli/draw.c
DATA_FILE=src/model/tetrominos.c
ACTION_FILE=src/gui/cli/action.c
TEST_FILE=src/tests/tests.c

install:
	@mkdir -p ${BIN_DIR} 
	@${GCC} ${MAIN_FILE} ${DATA_FILE} ${TETRIS_FILE} ${DRAW_FILE} ${ACTION_FILE} -o ${BIN_DIR}/${TARGET} -lncurses
	@echo "-------------------------------------------"
	@echo "Installed ${TARGET} to ${BIN_DIR}"
	@echo "-------------------------------------------"

uninstall:
	@rm -rf ${BIN_DIR}
	@echo "-------------------------------------------"
	@echo "Uninstall ${TARGET} and ${BIN_DIR}"
	@echo "-------------------------------------------"

test:
	@rm -rf ${TEST_DIR}
	@mkdir ${TEST_DIR}
	@${GCC} ${TEST_FILE} ${DATA_FILE} ${TETRIS_FILE} ${DRAW_FILE} ${ACTION_FILE} -o ${TEST_DIR}/${TEST_TARGET} -lcheck -lncurses
	@./${TEST_DIR}/${TEST_TARGET}
	@echo "-------------------------------------------"
	@echo "Tests are done"
	@echo "-------------------------------------------"

gcov_report: test
	@rm -rf ${COVERAGE_DIR}
	@${GCC} ${TEST_FILE} ${DATA_FILE} ${TETRIS_FILE} ${DRAW_FILE} ${ACTION_FILE} ${GCOV_FLAGS} -o ${TEST_DIR}/${TEST_TARGET} -lcheck -lncurses
	./${TEST_DIR}/${TEST_TARGET}
	@mkdir ${COVERAGE_DIR}
	lcov --capture --directory . --output-file ${COVERAGE_DIR}/coverage.info
	genhtml ${COVERAGE_DIR}/coverage.info --output-directory ${COVERAGE_DIR}/${COVERAGE_REPORT_DIR}
	open ${COVERAGE_DIR}/${COVERAGE_REPORT_DIR}/index.html
	@echo "-------------------------------------------"
	@echo "Coverage report is done"
	@echo "-------------------------------------------"

dist: clean
	@mkdir -p ${DIST_DIR}
	@tar -czf ${DIST_DIR}/${DIST_TARGET} --exclude=dist --exclude=.git --exclude=.gitignore .
	@echo "-------------------------------------------"
	@echo "Distribution tar is ready"
	@echo "-------------------------------------------"

clean: uninstall
	@rm -rf ${COVERAGE_DIR} ${TEST_DIR} ${DIST_DIR}
	@echo "-------------------------------------------"
	@echo "Remove artifacts"
	@echo "-------------------------------------------"

