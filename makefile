CC=g++

HDIR=header

_HEAD = prog.h glob.h peice.h bishop.h pawn.h game.h knight.h queen.h rook.h zer0.h
HEAD = $(patsubst %,$(HDIR)/%,$(_HEAD))

build: $(HEAD) prog.cpp
	@$(CC) -o Zer0 prog.cpp

.PHONY: clean

clean: 
	@rm -rf ./Zer0
