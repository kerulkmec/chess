CXX=g++
LD=g++
CFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb

all: compile doc

compile: piece.o board.o game.o main.o
	$(LD) -o keruloli piece.o board.o game.o main.o

piece.o: ./src/piece.cpp ./src/piece.h
	$(CXX) $(CFLAGS) -c -o $@ $<

board.o: ./src/board.cpp ./src/board.h
	$(CXX) $(CFLAGS) -c -o $@ $<

game.o: ./src/game.cpp ./src/game.h
	$(CXX) $(CFLAGS) -c -o $@ $<

main.o: ./src/main.cpp ./src/piece.h ./src/board.h ./src/game.h
	$(CXX) $(CFLAGS) -c -o $@ $<

run:
	./keruloli

doc:
	doxygen

clean:
	rm -f keruloli piece.o board.o game.o main.o
	rm -rf doc 

 