CXX=g++
CXXFLAGS= -Wall -MMD -g -lpthread -lX11 -std=c++0x # for shared_ptr
OBJS=window.o block.o board.o brick.o grid.o interpreter.o level.o RndNumGenerator.o blockFactoryLevel0.o blockFactoryLevel1.o blockFactoryLevel2.o blockFactoryLevel3.o \
	drop.o moveDown.o moveLeft.o moveRight.o rotateCCW.o rotateCW.o lvlUp.o lvlDown.o restart.o \
	iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o
MAIN_OBJS=main.o quadris.o ${OBJS}
EXEC=quadris

TEST_EXEC=${LEVEL_TEST_EXEC} ${BLOCK_TEST_EXEC} ${BLOCKFACTORY_TEST_EXEC}
LEVEL_TEST_OBJS=${OBJS} testLevel.o
LEVEL_TEST_EXEC=testLevel
BLOCK_TEST_OBJS=${OBJS} testBlock.o
BLOCK_TEST_EXEC=testBlock
BLOCKFACTORY_TEST_OBJS=${OBJS} testBlockFactory.o
BLOCKFACTORY_TEST_EXEC=testBlockFactory

DEPENDS=${OBJS:.o=.d}

all: ${EXEC} ${TEST_EXEC}
	rm -f *.d

${EXEC}: ${MAIN_OBJS}
	${CXX} ${CXXFLAGS} ${MAIN_OBJS} -o $@

clean:
	rm -f ${EXEC} ${TEST_EXEC} *.o *.d

test: test_level test_block test_blockFactory


test_level: ${LEVEL_TEST_EXEC}
	rm -f *.d

${LEVEL_TEST_EXEC}: ${LEVEL_TEST_OBJS}
	${CXX} ${CXXFLAGS} ${LEVEL_TEST_OBJS} -o $@

test_block: ${BLOCK_TEST_EXEC}
	rm -f *.d

${BLOCK_TEST_EXEC}: ${BLOCK_TEST_OBJS}
	${CXX} ${CXXFLAGS} ${BLOCK_TEST_OBJS} -o $@

test_blockFactory: ${BLOCKFACTORY_TEST_EXEC}
	rm -f *.d

${BLOCKFACTORY_TEST_EXEC}: ${BLOCKFACTORY_TEST_OBJS}
	${CXX} ${CXXFLAGS} ${BLOCKFACTORY_TEST_OBJS} -o $@

-include ${DEPENDS}
