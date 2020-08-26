CC  = $(shell (which gcc))
SRC = $(shell (find src -name "*.c" -type f))

BIN = njvm.exe

all:
	$(CC) -std=c99 $(SRC) -o ./bin/$(BIN)

vars:
	@echo $(CC)
	@echo $(SRC)