#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vm_opcodes.h"
#include "lib/vm_string.h"

/**
 * @brief OpCode mapping.
 */
#define _nop             (0x00)
#define _aconst_null     (0x01)
#define _iconst_m1       (0x02)
#define _iconst_0        (0x03)
#define _iconst_1        (0x04)
#define _iconst_2        (0x05)
#define _iconst_3        (0x06)
#define _iconst_4        (0x07)
#define _iconst_5        (0x08)
#define _lconst_0        (0x09)
#define _lconst_1        (0x0a)
#define _fconst_0        (0x0b)
#define _fconst_1        (0x0c)
#define _fconst_2        (0x0d)
#define _dconst_0        (0x0e)
#define _dconst_1        (0x0f)
#define _bipush          (0x10)
#define _sipush          (0x11)
#define _ldc             (0x12)
#define _ldc_w           (0x13)
#define _ldc2_w          (0x14)
#define _iload           (0x15)
#define _lload           (0x16)
#define _fload           (0x17)
#define _dload           (0x18)
#define _aload           (0x19)
#define _iload_0         (0x1a)
#define _iload_1         (0x1b)
#define _iload_2         (0x1c)
#define _iload_3         (0x1d)
#define _lload_0         (0x1e)
#define _lload_1         (0x1f)
#define _lload_2         (0x20)
#define _lload_3         (0x21)
#define _fload_0         (0x22)
#define _fload_1         (0x23)
#define _fload_2         (0x24)
#define _fload_3         (0x25)
#define _dload_0         (0x26)
#define _dload_1         (0x27)
#define _dload_2         (0x28)
#define _dload_3         (0x29)
#define _aload_0         (0x2a)
#define _aload_1         (0x2b)
#define _aload_2         (0x2c)
#define _aload_3         (0x2d)
#define _iaload          (0x2e)
#define _laload          (0x2f)
#define _faload          (0x30)
#define _daload          (0x31)
#define _aaload          (0x32)
#define _baload          (0x33)
#define _caload          (0x34)
#define _saload          (0x35)
#define _istore          (0x36)
#define _lstore          (0x37)
#define _fstore          (0x38)
#define _dstore          (0x39)
#define _astore          (0x3a)
#define _istore_0        (0x3b)
#define _istore_1        (0x3c)
#define _istore_2        (0x3d)
#define _istore_3        (0x3e)
#define _lstore_0        (0x3f)
#define _lstore_1        (0x40)
#define _lstore_2        (0x41)
#define _lstore_3        (0x42)
#define _fstore_0        (0x43)
#define _fstore_1        (0x44)
#define _fstore_2        (0x45)
#define _fstore_3        (0x46)
#define _dstore_0        (0x47)
#define _dstore_1        (0x48)
#define _dstore_2        (0x49)
#define _dstore_3        (0x4a)
#define _astore_0        (0x4b)
#define _astore_1        (0x4c)
#define _astore_2        (0x4d)
#define _astore_3        (0x4e)
#define _iastore         (0x4f)
#define _lastore         (0x50)
#define _fastore         (0x51)
#define _dastore         (0x52)
#define _aastore         (0x53)
#define _bastore         (0x54)
#define _castore         (0x55)
#define _sastore         (0x56)
#define _pop             (0x57)
#define _pop2            (0x58)
#define _dup             (0x59)
#define _dup_x1          (0x5a)
#define _dup_x2          (0x5b)
#define _dup2            (0x5c)
#define _dup2_x1         (0x5d)
#define _dup2_x2         (0x5e)
#define _swap            (0x5f)
#define _iadd            (0x60)
#define _ladd            (0x61)
#define _fadd            (0x62)
#define _dadd            (0x63)
#define _isub            (0x64)
#define _lsub            (0x65)
#define _fsub            (0x66)
#define _dsub            (0x67)
#define _imul            (0x68)
#define _lmul            (0x69)
#define _fmul            (0x6a)
#define _dmul            (0x6b)
#define _idiv            (0x6c)
#define _ldiv            (0x6d)
#define _fdiv            (0x6e)
#define _ddiv            (0x6f)
#define _irem            (0x70)
#define _lrem            (0x71)
#define _frem            (0x72)
#define _drem            (0x73)
#define _ineg            (0x74)
#define _lneg            (0x75)
#define _fneg            (0x76)
#define _dneg            (0x77)
#define _ishl            (0x78)
#define _lshl            (0x79)
#define _ishr            (0x7a)
#define _lshr            (0x7b)
#define _iushr           (0x7c)
#define _lushr           (0x7d)
#define _iand            (0x7e)
#define _land            (0x7f)
#define _ior             (0x80)
#define _lor             (0x81)
#define _ixor            (0x82)
#define _lxor            (0x83)
#define _iinc            (0x84)
#define _i2l             (0x85)
#define _i2f             (0x86)
#define _i2d             (0x87)
#define _l2i             (0x88)
#define _l2f             (0x89)
#define _l2d             (0x8a)
#define _f2i             (0x8b)
#define _f2l             (0x8c)
#define _f2d             (0x8d)
#define _d2i             (0x8e)
#define _d2l             (0x8f)
#define _d2f             (0x90)
#define _i2b             (0x91)
#define _i2c             (0x92)
#define _i2s             (0x93)
#define _lcmp            (0x94)
#define _fcmpl           (0x95)
#define _fcmpg           (0x96)
#define _dcmpl           (0x97)
#define _dcmpg           (0x98)
#define _ifeq            (0x99)
#define _ifne            (0x9a)
#define _iflt            (0x9b)
#define _ifge            (0x9c)
#define _ifgt            (0x9d)
#define _ifle            (0x9e)
#define _if_icmpeq       (0x9f)
#define _if_icmpne       (0xa0)
#define _if_icmplt       (0xa1)
#define _if_icmpge       (0xa2)
#define _if_icmpgt       (0xa3)
#define _if_icmple       (0xa4)
#define _if_acmpeq       (0xa5)
#define _if_acmpne       (0xa6)
#define _goto            (0xa7)
#define _jsr             (0xa8)
#define _ret             (0xa9)
#define _tableswitch     (0xaa)
#define _lookupswitch    (0xab)
#define _ireturn         (0xac)
#define _lreturn         (0xad)
#define _freturn         (0xae)
#define _dreturn         (0xaf)
#define _areturn         (0xb0)
#define _return          (0xb1)
#define _getstatic       (0xb2)
#define _putstatic       (0xb3)
#define _getfield        (0xb4)
#define _putfield        (0xb5)
#define _invokevirtual   (0xb6)
#define _invokespecial   (0xb7)
#define _invokestatic    (0xb8)
#define _invokeinterface (0xb9)
#define _invokedynamic   (0xba)
#define _new             (0xbb)
#define _newarray        (0xbc)
#define _anewarray       (0xbd)
#define _arraylength     (0xbe)
#define _athrow          (0xbf)
#define _checkcast       (0xc0)
#define _instanceof      (0xc1)
#define _monitorenter    (0xc2)
#define _monitorexit     (0xc3)
#define _wide            (0xc4)
#define _multianewarray  (0xc5)
#define _ifnull          (0xc6)
#define _ifnonnull       (0xc7)
#define _goto_w          (0xc8)
#define _jsr_w           (0xc9)

FILE * error_log;

void vm_error_log(char *s) {
    error_log = fopen("log.txt", "a+");
    fprintf(error_log, "%s", s);
    fclose(error_log);
}

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
                        vm_uint16_string_t *uint16_string = vm_utf8_to_uint16_t(
                            current_constant_pool[string_index].info.utf8_info.length,
                            current_constant_pool[string_index].info.utf8_info.bytes
                        );

                        char *buffer = calloc(uint16_string->length, sizeof(char));

                        for (int j = 0; j < uint16_string->length; j++) {
                            sprintf(&(buffer[j]), "%lc", uint16_string->string[j]);
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
                vm_uint16_string_t *class_name_string = vm_utf8_to_uint16_t(class_name.length, class_name.bytes);
                char *class_name_buffer = calloc(class_name_string->length, sizeof(char));

                for (int j = 0; j < class_name_string->length; j++) {
                    sprintf(&(class_name_buffer[j]), "%lc", class_name_string->string[j]);
                }

                uint16_t method_name_index = current_constant_pool[name_and_type_index].info.nameandtype_info.name_index;
                vm_utf8_t method_name = current_constant_pool[method_name_index].info.utf8_info;
                vm_uint16_string_t *method_name_string = vm_utf8_to_uint16_t(method_name.length, method_name.bytes);
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
                switch (atype)
                {
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
