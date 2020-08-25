CC  = $(shell (which gcc))
SRC = $(shell (find src -name "*.c" -type f))

BIN = njvm.exe

all:
	$(CC) -std=c99 $(SRC) -o ./bin/$(BIN)

test:
	@echo nothing to test for now

vars:
	@echo $(CC)
	@echo $(SRC)