CC  = $(shell (which gcc))
CC_FLAGS = -std=c99
CC_FLAGS_D = -std=c99 -g

JAVAC = $(shell (which javac))

# The entire source
SRC  = $(shell (find src -name "*.c" -type f))
# The source code files without main
SRC2 = $(shell (find src \( -name "*.c" ! -name "main.c" \) -type f))

JAVA_SRC = $(shell (find bin/java/ -name "*.java" -type f))

BIN = njvm.exe

TESTS_SRC = $(shell (find tests -maxdepth 1 -name "*.c" -type f))
# set of programs inside the tests source directory
TESTS_PRO = $(patsubst %.c,%,$(TESTS_SRC))
TESTS_UTI = $(shell (find tests/utils/ -name "*.c" -type f))

MUNIT     = $(shell (find tests/munit/ -name "*.c" -type f))

I_FLAG = -I./src/
L_FLAG = -lm

all:
	$(CC) $(CC_FLAGS) $(SRC) $(L_FLAG) -o ./bin/$(BIN)

debug:
	$(CC) $(CC_FLAGS_D) $(SRC) $(L_FLAG) -o ./bin/$(BIN)

%: %.c
	$(CC) $(CC_FLAGS) $(I_FLAG) $(SRC2) $(TESTS_UTI) $(MUNIT) $(L_FLAG) -o $@.out $<

test: $(TESTS_PRO)

java:
	$(JAVAC) $(JAVA_SRC)

vars:
	@echo "COMPILER:     $(CC)"
	@echo "SOURCE FILES: $(SRC)"
	@echo "TESTS FILES:  $(TESTS_SRC)"
	@echo "MUNIT FILES:  $(MUNIT)"
	@echo "TESTS UTILS FILES:  $(TESTS_UTI)"
	@echo "JAVA FILES: $(JAVA_SRC)"


.PHONY: clean
clean:
	rm -f ./bin/$(BIN)
	rm -f ./tests/*.out