CC  = $(shell (which gcc))
CC_FLAGS = -std=c99

# The entire source
SRC  = $(shell (find src -name "*.c" -type f))
# The source code files without main
SRC2 = $(shell (find src \( -name "*.c" ! -name "main.c" \) -type f))

BIN = njvm.exe

TESTS_SRC = $(shell (find tests -maxdepth 1 -name "*.c" -type f))
# set of programs inside the tests source directory
TESTS_PRO = $(patsubst %.c,%,$(TESTS_SRC))
TESTS_UTI = $(shell (find tests/utils/ -name "*.c" -type f))

MUNIT     = $(shell (find tests/munit/ -name "*.c" -type f))

I_FLAG = -I./src/
L_FLAG = -lm

all:
	$(CC) $(CC_FLAGS) -std=c99 $(SRC) -o ./bin/$(BIN)

%: %.c
	$(CC) $(CC_FLAGS) $(L_FLAG) $(I_FLAG) $(SRC2) $(TESTS_UTI) $(MUNIT) -o $@.out $<

test: $(TESTS_PRO)

vars:
	@echo "COMPILER:     $(CC)"
	@echo "SOURCE FILES: $(SRC)"
	@echo "TESTS FILES:  $(TESTS_SRC)"
	@echo "MUNIT FILES:  $(MUNIT)"
	@echo "TESTS UTILS FILES:  $(TESTS_UTI)"


.PHONY: clean
clean:
	rm -f ./bin/$(BIN)