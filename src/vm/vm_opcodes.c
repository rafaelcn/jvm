#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vm_opcodes.h"
#include "lib/vm_string.h"

uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK) {
    uint8_t _WIDE = 0;

    vm_local_variables_t *current_local_variables = STACK->local_variables;
    vm_cp_info_t *current_constant_pool = STACK->constant_pool;

    for (uint8_t i = 0; i <= _WIDE; i++) {
        switch (code[pc]) {
        case _nop:
            pc += 1;
            break;

        case _aconst_null:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = NULL;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iconst_m1:
        case _iconst_0:
        case _iconst_1:
        case _iconst_2:
        case _iconst_3:
        case _iconst_4:
        case _iconst_5:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = code[pc] - _iconst_0;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lconst_0:
        case _lconst_1:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (long) (code[pc] - _lconst_0);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fconst_0:
        case _fconst_1:
        case _fconst_2:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = (float) (code[pc] - _fconst_0);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dconst_0:
        case _dconst_1:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = (double) (code[pc] - _dconst_0);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _bipush:
            {
                uint8_t byte = code[pc+1];

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = byte;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _sipush:
            {
                uint8_t byte1 = code[pc+1];
                uint8_t byte2 = code[pc+2];

                short si = (byte1 << 8) | byte2;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = si;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _ldc:
        case _ldc_w:
        case _ldc2_w:
            {
                uint16_t index = 0;

                if (code[pc] - _ldc) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                } else {
                    index = code[pc+1];
                }

                switch (current_constant_pool[index].tag) {
                case 3: // Integer
                    {
                        int _i = current_constant_pool[index].info.integer_info.bytes;

                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _float;
                        new_frame->operand.value._float = (float) _i;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                    break;

                case 4: // Float
                    {
                        float _f = vm_itof(current_constant_pool[index].info.float_info.bytes);

                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _float;
                        new_frame->operand.value._float = _f;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                    break;

                case 5: // Long
                    {
                        long _l = vm_itol(
                            current_constant_pool[index].info.long_info.low_bytes,
                            current_constant_pool[index].info.long_info.high_bytes
                        );

                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _long;
                        new_frame->operand.value._long = _l;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                    break;

                case 6: // Double
                    {
                        double _d = vm_itod(
                            current_constant_pool[index].info.double_info.low_bytes,
                            current_constant_pool[index].info.double_info.high_bytes
                        );

                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _double;
                        new_frame->operand.value._double = _d;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                    break;

                case 8: // String
                    {
                        uint16_t string_index = current_constant_pool[index].info.string_info.string_index;
                        vm_uint32_string_t *string_t = vm_utf8_to_uint32_t(
                            current_constant_pool[string_index].info.utf8_info.length,
                            current_constant_pool[string_index].info.utf8_info.bytes
                        );

                        char *buffer = calloc(string_t->length, sizeof(char));

                        for (int j = 0; j < string_t->length; j++) {
                            sprintf(&(buffer[j]), "%lc", string_t->string[j]);
                        }

                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _string;
                        new_frame->operand.value._string = buffer;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                    break;

                default:
                    break;
                }
            }
            if (code[pc] - _ldc) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _iload:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = current_local_variables[index].value._int;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            break;

        case _lload:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = current_local_variables[index].value._long;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            break;

        case _fload:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = current_local_variables[index].value._float;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            break;

        case _dload:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = current_local_variables[index].value._double;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            break;

        case _aload:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = current_local_variables[index].value._reference;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            break;

        case _iload_0:
        case _iload_1:
        case _iload_2:
        case _iload_3:
            {
                uint8_t index = code[pc] - _iload_0;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = current_local_variables[index].value._int;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lload_0:
        case _lload_1:
        case _lload_2:
        case _lload_3:
            {
                uint8_t index = code[pc] - _lload_0;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = current_local_variables[index].value._long;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fload_0:
        case _fload_1:
        case _fload_2:
        case _fload_3:
            {
                uint16_t index = code[pc] - _fload_0;
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = current_local_variables[index].value._float;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dload_0:
        case _dload_1:
        case _dload_2:
        case _dload_3:
            {
                uint16_t index = code[pc] - _dload_0;
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = current_local_variables[index].value._double;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _aload_0:
        case _aload_1:
        case _aload_2:
        case _aload_3:
            {
                uint8_t index = code[pc] - _aload_0;
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = current_local_variables[index].value._reference;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iaload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _laload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                long *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _faload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                float *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _daload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                double *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _aaload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                void **array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _baload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                uint8_t *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _byte_or_bool;
                new_frame->operand.value._byte_or_bool = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _caload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                char *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _char;
                new_frame->operand.value._char = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _saload:
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                short *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _short;
                new_frame->operand.value._short = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _istore:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                current_local_variables[index].type = _int;
                current_local_variables[index].value._int = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
            }
            break;

        case _lstore:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                current_local_variables[index].type = _long;
                current_local_variables[index].value._long = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
            }
            break;

        case _fstore:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                current_local_variables[index].type = _float;
                current_local_variables[index].value._float = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
            }
            break;

        case _dstore:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                current_local_variables[index].type = _double;
                current_local_variables[index].value._double = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
            }
            break;

        case _astore:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                current_local_variables[index].type = _reference;
                current_local_variables[index].value._reference = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;
            }
            break;

        case _istore_0:
        case _istore_1:
        case _istore_2:
        case _istore_3:
            {
                uint8_t index = code[pc] - _istore_0;

                current_local_variables[index].type = _int;
                current_local_variables[index].value._int = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
            }
            pc += 1;
            break;

        case _lstore_0:
        case _lstore_1:
        case _lstore_2:
        case _lstore_3:
            {
                uint8_t index = code[pc] - _lstore_0;

                current_local_variables[index].type = _long;
                current_local_variables[index].value._long = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
            }
            pc += 1;
            break;

        case _fstore_0:
        case _fstore_1:
        case _fstore_2:
        case _fstore_3:
            {
                uint8_t index = code[pc] - _fstore_0;

                current_local_variables[index].type = _float;
                current_local_variables[index].value._float = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
            }
            pc += 1;
            break;

        case _dstore_0:
        case _dstore_1:
        case _dstore_2:
        case _dstore_3:
            {
                uint8_t index = code[pc] - _dstore_0;

                current_local_variables[index].type = _double;
                current_local_variables[index].value._double = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
            }
            pc += 1;
            break;

        case _astore_0:
        case _astore_1:
        case _astore_2:
        case _astore_3:
            {
                uint8_t index = code[pc] - _astore_0;

                current_local_variables[index].type = _reference;
                current_local_variables[index].value._reference = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;
            }
            pc += 1;
            break;

        case _iastore:
            {
                int value= pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int *array = (int *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _lastore:
            {
                int value= pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                long *array = (long *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _fastore:
            {
                float value= pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                float *array = (float *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _dastore:
            {
                double value= pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                double *array = (double *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _aastore:
            {
                void *value= pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                void **array = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _bastore:
            {
                uint8_t value= pop_from_ostack(&(STACK->operand_stack))->operand.value._byte_or_bool;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                uint8_t *array = (uint8_t *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _castore:
            {
                char value= pop_from_ostack(&(STACK->operand_stack))->operand.value._char;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                char *array = (char *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _sastore:
            {
                short value= pop_from_ostack(&(STACK->operand_stack))->operand.value._short;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                short *array = (short *) pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                array[index] = value;
            }
            pc += 1;
            break;

        case _pop:
        case _pop2:
            {
                if (code[pc] - _pop) {
                    pop_from_ostack(&(STACK->operand_stack));
                }

                pop_from_ostack(&(STACK->operand_stack));
            }
            pc += 1;
            break;

        case _dup:
        case _dup_x1:
        case _dup_x2:
            {
                vm_ostack_t *value1 = pop_from_ostack(&(STACK->operand_stack));
                vm_ostack_t *value1_cp = calloc(1, sizeof(vm_ostack_t));
                value1_cp->operand.type = value1->operand.type;
                value1_cp->next_frame = NULL;

                switch (value1_cp->operand.type) {
                case _short:
                    value1_cp->operand.value._short = value1->operand.value._short;
                    break;
                case _int:
                    value1_cp->operand.value._int = value1->operand.value._int;
                    break;
                case _long:
                    value1_cp->operand.value._long = value1->operand.value._long;
                    break;
                case _float:
                    value1_cp->operand.value._float = value1->operand.value._float;
                    break;
                case _double:
                    value1_cp->operand.value._double = value1->operand.value._double;
                    break;
                case _char:
                    value1_cp->operand.value._char = value1->operand.value._char;
                    break;
                case _string:
                    value1_cp->operand.value._string = value1->operand.value._string;
                    break;
                case _byte_or_bool:
                    value1_cp->operand.value._byte_or_bool = value1->operand.value._byte_or_bool;
                    break;
                case _reference:
                    value1_cp->operand.value._reference = value1->operand.value._reference;
                    break;
                case _returnAddress:
                    value1_cp->operand.value._returnAddress = value1->operand.value._returnAddress;
                    break;
                default:
                    break;
                }

                switch (code[pc]) {
                case _dup:
                    push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                    push_into_ostack(&(STACK->operand_stack), &(value1));
                    break;

                case _dup_x1:
                    {
                        vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));

                        push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                        push_into_ostack(&(STACK->operand_stack), &(value2));
                        push_into_ostack(&(STACK->operand_stack), &(value1));
                    }
                    break;

                case _dup_x2:
                    {
                        vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));

                        if ((value2->operand.type == _long) || (value2->operand.type == _double)) {
                            push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                            push_into_ostack(&(STACK->operand_stack), &(value2));
                            push_into_ostack(&(STACK->operand_stack), &(value1));
                        } else {
                            vm_ostack_t *value3 = pop_from_ostack(&(STACK->operand_stack));

                            push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                            push_into_ostack(&(STACK->operand_stack), &(value3));
                            push_into_ostack(&(STACK->operand_stack), &(value2));
                            push_into_ostack(&(STACK->operand_stack), &(value1));
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            pc += 1;
            break;

        case _dup2:
        case _dup2_x1:
        case _dup2_x2:
            {
                vm_ostack_t *value1 = pop_from_ostack(&(STACK->operand_stack));
                vm_ostack_t *value1_cp = calloc(1, sizeof(vm_ostack_t));
                value1_cp->operand.type = value1->operand.type;
                value1_cp->next_frame = NULL;

                switch (value1_cp->operand.type) {
                case _short:
                    value1_cp->operand.value._short = value1->operand.value._short;
                    break;
                case _int:
                    value1_cp->operand.value._int = value1->operand.value._int;
                    break;
                case _long:
                    value1_cp->operand.value._long = value1->operand.value._long;
                    break;
                case _float:
                    value1_cp->operand.value._float = value1->operand.value._float;
                    break;
                case _double:
                    value1_cp->operand.value._double = value1->operand.value._double;
                    break;
                case _char:
                    value1_cp->operand.value._char = value1->operand.value._char;
                    break;
                case _string:
                    value1_cp->operand.value._string = value1->operand.value._string;
                    break;
                case _byte_or_bool:
                    value1_cp->operand.value._byte_or_bool = value1->operand.value._byte_or_bool;
                    break;
                case _reference:
                    value1_cp->operand.value._reference = value1->operand.value._reference;
                    break;
                case _returnAddress:
                    value1_cp->operand.value._returnAddress = value1->operand.value._returnAddress;
                    break;
                default:
                    break;
                }

                if ((value1_cp->operand.type != _long) && (value1_cp->operand.type != _double)) {
                    vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));
                    vm_ostack_t *value2_cp = calloc(1, sizeof(vm_ostack_t));
                    value2_cp->operand.type = value2->operand.type;
                    value2_cp->next_frame = NULL;

                    switch (value2_cp->operand.type) {
                    case _short:
                        value2_cp->operand.value._short = value2->operand.value._short;
                        break;
                    case _int:
                        value2_cp->operand.value._int = value2->operand.value._int;
                        break;
                    case _long:
                        value2_cp->operand.value._long = value2->operand.value._long;
                        break;
                    case _float:
                        value2_cp->operand.value._float = value2->operand.value._float;
                        break;
                    case _double:
                        value2_cp->operand.value._double = value2->operand.value._double;
                        break;
                    case _char:
                        value2_cp->operand.value._char = value2->operand.value._char;
                        break;
                    case _string:
                        value2_cp->operand.value._string = value2->operand.value._string;
                        break;
                    case _byte_or_bool:
                        value2_cp->operand.value._byte_or_bool = value2->operand.value._byte_or_bool;
                        break;
                    case _reference:
                        value2_cp->operand.value._reference = value2->operand.value._reference;
                        break;
                    case _returnAddress:
                        value2_cp->operand.value._returnAddress = value2->operand.value._returnAddress;
                        break;
                    default:
                        break;
                    }

                    switch (code[pc]) {
                    case _dup2:
                        push_into_ostack(&(STACK->operand_stack), &(value2_cp));
                        push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                        push_into_ostack(&(STACK->operand_stack), &(value2));
                        push_into_ostack(&(STACK->operand_stack), &(value1));
                        break;

                    case _dup2_x1:
                        {
                            vm_ostack_t *value3 = pop_from_ostack(&(STACK->operand_stack));

                            push_into_ostack(&(STACK->operand_stack), &(value2_cp));
                            push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                            push_into_ostack(&(STACK->operand_stack), &(value3));
                            push_into_ostack(&(STACK->operand_stack), &(value2));
                            push_into_ostack(&(STACK->operand_stack), &(value1));
                        }
                        break;

                    case _dup2_x2:
                        {
                            vm_ostack_t *value3 = pop_from_ostack(&(STACK->operand_stack));

                            if ((value3->operand.type == _long) || (value3->operand.type == _double)) {
                                push_into_ostack(&(STACK->operand_stack), &(value2_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value3));
                                push_into_ostack(&(STACK->operand_stack), &(value2));
                                push_into_ostack(&(STACK->operand_stack), &(value1));
                            } else {
                                vm_ostack_t *value4 = pop_from_ostack(&(STACK->operand_stack));

                                push_into_ostack(&(STACK->operand_stack), &(value2_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value4));
                                push_into_ostack(&(STACK->operand_stack), &(value3));
                                push_into_ostack(&(STACK->operand_stack), &(value2));
                                push_into_ostack(&(STACK->operand_stack), &(value1));
                            }
                        }
                        break;
                    default:
                        break;
                    }
                } else {
                    switch (code[pc]) {
                    case _dup2:
                        push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                        push_into_ostack(&(STACK->operand_stack), &(value1));
                        break;

                    case _dup2_x1:
                        {
                            vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));

                            push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                            push_into_ostack(&(STACK->operand_stack), &(value2));
                            push_into_ostack(&(STACK->operand_stack), &(value1));
                        }
                        break;

                    case _dup2_x2:
                        {
                            vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));

                            if ((value2->operand.type == _long) || (value2->operand.type == _double)) {
                                push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value2));
                                push_into_ostack(&(STACK->operand_stack), &(value1));
                            } else {
                                vm_ostack_t *value3 = pop_from_ostack(&(STACK->operand_stack));

                                push_into_ostack(&(STACK->operand_stack), &(value1_cp));
                                push_into_ostack(&(STACK->operand_stack), &(value3));
                                push_into_ostack(&(STACK->operand_stack), &(value2));
                                push_into_ostack(&(STACK->operand_stack), &(value1));
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
            pc += 1;
            break;

        case _swap:
            {
                vm_ostack_t *value1 = pop_from_ostack(&(STACK->operand_stack));
                vm_ostack_t *value2 = pop_from_ostack(&(STACK->operand_stack));
                push_into_ostack(&(STACK->operand_stack), &(value1));
                push_into_ostack(&(STACK->operand_stack), &(value2));
            }
            break;

        case _iadd:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 + _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ladd:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 + _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fadd:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = _f1 + _f2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dadd:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = _d1 + _d2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _isub:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 - _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lsub:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 - _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fsub:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = _f1 - _f2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dsub:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = _d1 - _d2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _imul:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 * _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lmul:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 * _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fmul:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = _f1 * _f2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dmul:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = _d1 * _d2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _idiv:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 / _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ldiv:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 / _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fdiv:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = _f1 / _f2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ddiv:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = _d1 / _d2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _irem:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 - (_i1/_i2) * _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lrem:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 - (_l1/_l2) * _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _frem:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = _f1 - ((int) floor((_f1/_f2))) * _f2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _drem:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = _d1 - ((int) floor((_d1/_d2))) * _d2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ineg:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = 0 - _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lneg:
            {
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = 0 - _l;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fneg:
            {
                float _f = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = ((float) 0) - _f;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dneg:
            {
                double _d = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = ((double) 0) - _d;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ishl:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int s = (_i2 & 0x0000001F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (_i1 << s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lshl:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                int s = (_i & 0x0000003F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (_l << s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ishr:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int s = (_i2 & 0x0000001F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (_i1 >> s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lshr:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                int s = (_i & 0x0000003F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (_l >> s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iushr:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int s = (_i2 & 0x0000001F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (int) (((unsigned int) _i1) << s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lushr:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                int s = (_i & 0x0000003F);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (((unsigned long) _l) << s);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iand:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 & _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _land:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 & _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ior:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 | _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lor:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 | _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ixor:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = _i1 ^ _i2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lxor:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = _l1 ^ _l2;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iinc:
            {
                uint16_t index;
                int16_t const_value;

                if (_WIDE) {
                    index = (code[pc+1] << 8) | code[pc+2];
                    const_value = (code[pc+3] << 8) | code[pc+4];
                    pc += 5;
                } else {
                    index = code[pc+1];
                    const_value = code[pc+2];
                    pc += 3;
                }

                current_local_variables[index].value._int += const_value;
            }
            break;

        case _i2l:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (long) _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _i2f:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = (float) _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _i2d:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = (double) _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _l2i:
            {
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (int) _l;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _l2f:
            {
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = (float) _l;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _l2d:
            {
                long _l = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = (double) _l;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _f2i:
            {
                float _f = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (int) _f;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _f2l:
            {
                float _f = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (long) _f;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _f2d:
            {
                float _f = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = (double) _f;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _d2i:
            {
                double _d = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (int) _d;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _d2l:
            {
                double _d = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = (long) _d;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _d2f:
            {
                double _d = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = (float) _d;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _i2b:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (int8_t) _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _i2c:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (unsigned int) ((char) _i);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _i2s:
            {
                int _i = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = (short) _i;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _lcmp:
            {
                long _l2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
                long _l1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->next_frame = NULL;

                if (_l1 > _l2) {
                    new_frame->operand.value._int = 1;
                } else if (_l1 == _l2) {
                    new_frame->operand.value._int = 0;
                } else {
                    new_frame->operand.value._int = -1;
                }

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _fcmpl:
        case _fcmpg:
            {
                float _f2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
                float _f1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->next_frame = NULL;

                if (_f1 == NAN || _f2 == NAN) {
                    if (code[pc] - _fcmpl) {
                        new_frame->operand.value._int = 1;
                    } else {
                        new_frame->operand.value._int = -1;
                    }
                } else if (_f1 > _f2) {
                    new_frame->operand.value._int = 1;
                } else if (_f1 == _f2) {
                    new_frame->operand.value._int = 0;
                } else {
                    new_frame->operand.value._int = -1;
                }

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _dcmpl:
        case _dcmpg:
            {
                double _d2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
                double _d1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->next_frame = NULL;

                if (_d1 == NAN || _d2 == NAN) {
                    if (code[pc] - _dcmpl) {
                        new_frame->operand.value._int = 1;
                    } else {
                        new_frame->operand.value._int = -1;
                    }
                } else if (_d1 > _d2) {
                    new_frame->operand.value._int = 1;
                } else if (_d1 == _d2) {
                    new_frame->operand.value._int = 0;
                } else {
                    new_frame->operand.value._int = -1;
                }

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _ifeq:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value == 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _ifne:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value != 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _iflt:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value < 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _ifge:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value >= 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _ifgt:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value > 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _ifle:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (value <= 0) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmpeq:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 == _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmpne:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 != _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmplt:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 < _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmpge:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 >= _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmpgt:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 > _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_icmple:
            {
                int _i2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int _i1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                if (_i1 <= _i2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_acmpeq:
            {
                void *_a2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;
                void *_a1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                if (_a1 == _a2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _if_acmpne:
            {
                void *_a2 = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;
                void *_a1 = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                if (_a1 != _a2) {
                    uint8_t branchbyte1 = code[pc+1];
                    uint8_t branchbyte2 = code[pc+2];

                    int16_t offset = (branchbyte1 << 8) | branchbyte2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _goto:
            {
                uint8_t branchbyte1 = code[pc+1];
                uint8_t branchbyte2 = code[pc+2];

                int16_t offset = (branchbyte1 << 8) | branchbyte2;

                pc += offset;
            }
            break;

        case _jsr:
            {
                uint8_t branchbyte1 = code[pc+1];
                uint8_t branchbyte2 = code[pc+2];

                int16_t offset = (branchbyte1 << 8) | branchbyte2;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _returnAddress;
                new_frame->operand.value._returnAddress = pc + ((uint32_t) 3);
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                pc += offset;
            }
            break;

        case _ret:
            {
                uint16_t index = 0;

                if (_WIDE) {
                    uint8_t indexbyte1 = code[pc+1];
                    uint8_t indexbyte2 = code[pc+2];
                    index = (indexbyte1 << 8) | indexbyte2;
                    _WIDE = 0;
                    pc += 3;
                } else {
                    index = code[pc+1];
                    pc += 2;
                }

                pc = current_local_variables[index].value._returnAddress;
            }
            break;

        case _tableswitch:
        case _lookupswitch:
            break;

        case _ireturn:
            {
                int value = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = value;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _lreturn:
            {
                long value = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;

                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = value;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _freturn:
            {
                float value = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;

                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = value;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _dreturn:
            {
                double value = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;

                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = value;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _areturn:
            {
                void *value = pop_from_ostack(&(STACK->operand_stack))->operand.value._reference;

                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = value;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _return:
            {
                vm_stack_t *old_frame = STACK;
                old_frame->next_frame = NULL;

                STACK = STACK->next_frame;

                free(old_frame);

                if (STACK != NULL) {
                    pc = STACK->pc;
                } else {
                    pc = 0xFFFFFFFF;
                }
            }
            break;

        case _getstatic:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _string;
                new_frame->operand.value._string = calloc(10, sizeof(char));
                new_frame->next_frame = NULL;

                sprintf(new_frame->operand.value._string, "getstatic");
                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 3;
            break;

        case _invokevirtual:
        case _invokespecial:
            {
                uint8_t indexbyte1 = code[pc+1];
                uint8_t indexbyte2 = code[pc+2];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;

                uint16_t class_index = current_constant_pool[index].info.methodref_info.class_index;
                uint16_t name_and_type_index = current_constant_pool[index].info.methodref_info.name_and_type_index;

                uint16_t class_name_index = current_constant_pool[class_index].info.class_info.name_index;
                vm_utf8_t class_name = current_constant_pool[class_name_index].info.utf8_info;
                vm_uint32_string_t *class_name_string = vm_utf8_to_uint32_t(class_name.length, class_name.bytes);
                char *class_name_buffer = calloc(class_name_string->length, sizeof(char));

                for (int j = 0; j < class_name_string->length; j++) {
                    sprintf(&(class_name_buffer[j]), "%lc", class_name_string->string[j]);
                }

                uint16_t method_name_index = current_constant_pool[name_and_type_index].info.nameandtype_info.name_index;
                vm_utf8_t method_name = current_constant_pool[method_name_index].info.utf8_info;
                vm_uint32_string_t *method_name_string = vm_utf8_to_uint32_t(method_name.length, method_name.bytes);
                char *method_name_buffer = calloc(method_name_string->length, sizeof(char));

                for (int j = 0; j < method_name_string->length; j++) {
                    sprintf(&(method_name_buffer[j]), "%lc", method_name_string->string[j]);
                }

                if (vm_strcmp(class_name_buffer, "java/io/PrintStream")) {
                    if (vm_strcmp(method_name_buffer, "print") || vm_strcmp(method_name_buffer, "println")) {
                        vm_ostack_t *popped_operand = pop_from_ostack(&(STACK->operand_stack));

                        char newline = vm_strcmp(method_name_buffer, "print") ? '\0' : '\n';

                        switch (popped_operand->operand.type) {
                        case _int:
                            printf("%i%c", popped_operand->operand.value._int, newline);
                            break;

                        case _float:
                            printf("%f%c", popped_operand->operand.value._float, newline);
                            break;

                        case _long:
                            printf("%li%c", popped_operand->operand.value._long, newline);
                            break;

                        case _double:
                            printf("%lf%c", popped_operand->operand.value._double, newline);
                            break;

                        case _string:
                            printf("%s%c", popped_operand->operand.value._string, newline);
                            break;

                        default:
                            break;
                        }
                    }
                } else if (vm_strcmp(class_name_buffer, "java/lang/StringBuilder")) {
                    if (vm_strcmp(method_name_buffer, "<init>")) {
                        STACK->StringBuilder = realloc(STACK->StringBuilder, sizeof(char));
                        STACK->StringBuilder[0] = '\0';
                    } else if (vm_strcmp(method_name_buffer, "append")) {
                        vm_ostack_t *popped_operand = pop_from_ostack(&(STACK->operand_stack));

                        int size;
                        if (popped_operand->operand.type == _string) {
                            size = strlen(popped_operand->operand.value._string) + 1;
                        } else {
                            size = 80;
                        }

                        char buffer[size];

                        switch (popped_operand->operand.type) {
                        case _int:
                            size = sprintf(buffer, "%i", popped_operand->operand.value._int);
                            break;

                        case _float:
                            size = sprintf(buffer, "%f", popped_operand->operand.value._float);
                            break;

                        case _long:
                            size = sprintf(buffer, "%li", popped_operand->operand.value._long);
                            break;

                        case _double:
                            size = sprintf(buffer, "%lf", popped_operand->operand.value._double);
                            break;

                        case _string:
                            size = sprintf(buffer, "%s", popped_operand->operand.value._string);
                            break;

                        default:
                            break;
                        }

                        int offset = strlen(STACK->StringBuilder);

                        STACK->StringBuilder = realloc(STACK->StringBuilder, (size + 1));

                        for (int j = 0; j < (size + 1); j++) {
                            STACK->StringBuilder[j + offset] = buffer[j];
                        }
                    } else if (vm_strcmp(method_name_buffer, "toString")) {
                        vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                        new_frame->operand.type = _string;
                        new_frame->operand.value._string = STACK->StringBuilder;
                        new_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_frame));
                    }
                }
            }
            pc += 3;
            break;

        case _invokedynamic:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _string;
                new_frame->operand.value._string = calloc(14, sizeof(char));
                new_frame->next_frame = NULL;

                sprintf(new_frame->operand.value._string, "invokedynamic");
                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 5;
            break;

        case _new:
            {
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _string;
                new_frame->operand.value._string = calloc(4, sizeof(char));
                new_frame->next_frame = NULL;

                sprintf(new_frame->operand.value._string, "new");
                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 3;
            break;

        case _newarray:
            {
                int count = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
                int atype = code[pc+1];
                void *array;
                switch (atype) {
                case T_BOOLEAN:
                    array = calloc(count, sizeof(char));
                    break;
                case T_CHAR:
                    array = calloc(count, sizeof(char));
                    break;
                case T_FLOAT:
                    array = calloc(count, sizeof(float));
                    break;
                case T_DOUBLE:
                    array = calloc(count, sizeof(double));
                    break;
                case T_BYTE:
                    array = calloc(count, sizeof(char));
                    break;
                case T_SHORT:
                    array = calloc(count, sizeof(short));
                    break;
                case T_INT:
                    array = calloc(count, sizeof(int));
                    break;
                case T_LONG:
                    array = calloc(count, sizeof(long));
                    break;
                default:
                    array = NULL;
                    break;
                }

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _reference;
                new_frame->operand.value._reference = array;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _ifnull:
            {
                void *ref = NULL;

                vm_ostack_t *frame = pop_from_ostack(&(STACK->operand_stack));

                ref = frame->operand.value._reference;

                if (ref == NULL) {
                    uint8_t branch1 = code[pc+1];
                    uint8_t branch2 = code[pc+2];

                    uint16_t offset = (branch1 << 8) | branch2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _ifnonnull:
            {
                void *ref = NULL;

                vm_ostack_t *frame = pop_from_ostack(&(STACK->operand_stack));

                ref = frame->operand.value._reference;

                if (ref != NULL) {
                    uint8_t branch1 = code[pc+1];
                    uint8_t branch2 = code[pc+2];

                    uint16_t offset = (branch1 << 8) | branch2;

                    pc += offset;
                } else {
                    pc += 3;
                }
            }
            break;

        case _wide:
            _WIDE = 1;
            pc += 1;
            break;

        default:
            pc += 1;
            break;
        }
    }

    return pc;
}
