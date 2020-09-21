# nJVM

An implementation of (some characteristics of) the JVM in C.

# Build

Use make to compile.

# Usage

Deixando salvo aqui o comando pra compilar os testes
gcc tests/tests_vm_string.c tests/munit/munit.c src/vm/lib/vm_string.c src/vm/utils/vm_logger.c -std=c99 -Isrc/ -g
