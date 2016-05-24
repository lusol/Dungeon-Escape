CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = cc3k
OBJECTS = main.o controller.o view.o game.o floor.o chamber.o cell.o human.o object.o enemy.o player.o dwarf.o shade.o drow.o vampire.o goblin.o troll.o potioneffect.o halfling.o elf.o merchant.o orc.o dragon.o item.o potion.o rhpot.o phpot.o bapot.o wapot.o bdpot.o wdpot.o treasure.o dragontreasure.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d
#rm ${OBJECTS} ${EXEC} ${DEPENDS}
