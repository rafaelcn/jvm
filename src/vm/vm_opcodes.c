#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        case _iconst_m1:
        case _iconst_0:
        case _iconst_1:
        case _iconst_2:
        case _iconst_3:
        case _iconst_4:
        case _iconst_5:
            // Push the int constant <i> (-1, 0, 1, 2, 3, 4 or 5) onto the
            // operand stack.
            {
                vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                new_operand_frame->operand.type = _int;
                new_operand_frame->operand.value._int = code[pc] - _iconst_0;
                new_operand_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
            }
            pc += 1;
            break;

        case _bipush:
            // The immediate byte is sign-extended to an int value. That value
            // is pushed onto the operand stack.
            {
                signed char byte = code[pc+1];
                vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                new_operand_frame->operand.type = _int;
                new_operand_frame->operand.value._int = byte;
                new_operand_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
            }
            pc += 2;
            break;

        case _ldc:
            // The index is an unsigned byte that must be a valid index into the
            // run-time constant pool of the current class (§2.6).
            // If the run-time constant pool entry is a run-time constant of type
            // int or float, the numeric value of that run-time constant is pushed
            // onto the operand stack as an int or float, respectively.

            {
                uint8_t index = code[pc+1];

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

                case 8: // String
                    {
                        uint16_t string_index = current_constant_pool[index].info.string_info.string_index;
                        uint16_t *uint16_string = vm_utf8_to_uint16_t(
                            current_constant_pool[string_index].info.utf8_info.length,
                            current_constant_pool[string_index].info.utf8_info.bytes);


                        char buffer[sizeof(uint16_string)];

                        for (int j = 0; j < current_constant_pool[string_index].info.utf8_info.length; j++) {
                            sprintf(&(buffer[j]), "%lc", uint16_string[j]);
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
            pc += 2;
            break;

        case _ldc_w:
            // The unsigned indexbyte1 and indexbyte2 are assembled into an
            // unsigned 16-bit index into the run-time constant pool of the
            // current class (§2.6), where the value of the index is calculated as
            // (indexbyte1 << 8) | indexbyte2.
            // If the run-time constant pool entry is a run-time constant of type
            // int or float, the numeric value of that run-time constant is pushed
            // onto the operand stack as an int or float, respectively.
        case _ldc2_w:
            // The unsigned indexbyte1 and indexbyte2 are assembled into an
            // unsigned 16-bit index into the run-time constant pool of the
            // current class (§2.6), where the value of the index is calculated as
            // (indexbyte1 << 8) | indexbyte2.
            // The numeric value of that run-time constant is pushed onto the
            // operand stack as a long or double, respectively.
            {
                uint8_t indexbyte1 = code[pc+1];
                uint8_t indexbyte2 = code[pc+2];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;

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
                        uint16_t *uint16_string = vm_utf8_to_uint16_t(
                            current_constant_pool[string_index].info.utf8_info.length,
                            current_constant_pool[string_index].info.utf8_info.bytes);

                        char buffer[current_constant_pool[string_index].info.utf8_info.length];

                        for (int j = 0; j < current_constant_pool[string_index].info.utf8_info.length; j++) {
                            sprintf(&(buffer[j]), "%lc", uint16_string[j]);
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
            pc += 3;
            break;

        case _iload:
            // The index is an unsigned byte that must be an index into the local
            // variable array of the current frame (§2.6). The local variable at
            // index must contain an int. The value of the local variable at index
            // is pushed onto the operand stack
            {
                uint8_t index = code[pc+1];

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = current_local_variables[index].value._int;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _lload:
            // The index is an unsigned byte. Both index and index+1 must be
            // indices into the local variable array of the current frame (§2.6).
            // The local variable at index must contain a long. The value of the
            // local variable at index is pushed onto the operand stack.
            {
                uint8_t index = code[pc+1];

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _long;
                new_frame->operand.value._long = current_local_variables[index].value._long;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _fload:
            // The index is an unsigned byte that must be an index into the local
            // variable array of the current frame (§2.6). The local variable at
            // index must contain a float. The value of the local variable at index
            // is pushed onto the operand stack.
            {
                uint8_t index = code[pc+1];

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _float;
                new_frame->operand.value._float = current_local_variables[index].value._float;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _dload:
            // The index is an unsigned byte. Both index and index+1 must be
            // indices into the local variable array of the current frame (§2.6).
            // The local variable at index must contain a double. The value of
            // the local variable at index is pushed onto the operand stack.
            {
                uint8_t index = code[pc+1];

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _double;
                new_frame->operand.value._double = current_local_variables[index].value._double;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _aload:
            // The index is an unsigned byte that must be an index into the local
            // variable array of the current frame (§2.6). The local variable at
            // index must contain a reference. The objectref in the local variable
            // at index is pushed onto the operand stack.
            {
                uint8_t index = code[pc+1];
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _array;
                new_frame->operand.value._array = current_local_variables[index].value._array;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 2;
            break;

        case _iload_0:
        case _iload_1:
        case _iload_2:
        case _iload_3:
            // The <n> must be an index into the local variable array of the
            // current frame (§2.6). The local variable at <n> must contain an
            // int. The value of the local variable at <n> is pushed onto the
            // operand stack.
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
            // Both <n> and <n>+1 must be indices into the local variable array
            // of the current frame (§2.6). The local variable at <n> must contain
            // a long. The value of the local variable at <n> is pushed onto the
            // operand stack.
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
            // The <n> must be an index into the local variable array of the
            // current frame (§2.6). The local variable at <n> must contain a
            // float. The value of the local variable at <n> is pushed onto the
            // operand stack.
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
            // Both <n> and <n>+1 must be indices into the local variable array
            // of the current frame (§2.6). The local variable at <n> must contain
            // a double. The value of the local variable at <n> is pushed onto
            // the operand stack.
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
            // The <n> must be an index into the local variable array of the
            // current frame (§2.6). The local variable at <n> must contain a
            // reference. The objectref in the local variable at <n> is pushed
            // onto the operand stack.
            {
                uint8_t index = code[pc] - _aload_0;
                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _array;
                new_frame->operand.value._array = current_local_variables[index].value._array;
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _iaload:
            // The arrayref must be of type reference and must refer to an array
            // whose components are of type int. The index must be of type int.
            // Both arrayref and index are popped from the operand stack. The
            // int value in the component of the array at index is retrieved and
            // pushed onto the operand stack.
            {
                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;


                int *array = pop_from_ostack(&(STACK->operand_stack))->operand.value._array;

                vm_ostack_t *new_frame = calloc(1, sizeof(vm_ostack_t));

                new_frame->operand.type = _int;
                new_frame->operand.value._int = array[index];
                new_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_frame));
            }
            pc += 1;
            break;

        case _istore:
            // The index is an unsigned byte that must be an index into the local
            // variable array of the current frame (§2.6). The value on the top
            // of the operand stack must be of type int. It is popped from the
            // operand stack, and the value of the local variable at index is set
            // to value.
            {
                uint8_t index = code[pc+1];

                current_local_variables[index].type = _int;
                current_local_variables[index].value._int = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;
            }
            pc += 2;
            break;

        case _lstore:
            // The index is an unsigned byte. Both index and index+1 must be
            // indices into the local variable array of the current frame (§2.6).
            // The value on the top of the operand stack must be of type long. It
            // is popped from the operand stack, and the local variables at index
            // and index+1 are set to value.
            {
                uint8_t index = code[pc+1];

                current_local_variables[index].type = _long;
                current_local_variables[index].value._long = pop_from_ostack(&(STACK->operand_stack))->operand.value._long;
            }
            pc += 2;
            break;

        case _fstore:
            // The index is an unsigned byte that must be an index into the local
            // variable array of the current frame (§2.6). The value on the top
            // of the operand stack must be of type float. It is popped from
            // the operand stack and undergoes value set conversion (§2.8.3),
            // resulting in value'. The value of the local variable at index is set
            // to value'.
            {
                uint8_t index = code[pc+1];

                current_local_variables[index].type = _float;
                current_local_variables[index].value._float = pop_from_ostack(&(STACK->operand_stack))->operand.value._float;
            }
            pc += 2;
            break;

        case _dstore:
            // The index is an unsigned byte. Both index and index+1 must be
            // indices into the local variable array of the current frame (§2.6).
            // The value on the top of the operand stack must be of type double.
            // It is popped from the operand stack and undergoes value set
            // conversion (§2.8.3), resulting in value'. The local variables at index
            // and index+1 are set to value'.
            {
                uint8_t index = code[pc+1];

                current_local_variables[index].type = _double;
                current_local_variables[index].value._double = pop_from_ostack(&(STACK->operand_stack))->operand.value._double;
            }
            pc += 2;
            break;

        case _astore:
            // The arrayref must be of type reference and must refer to
            // an array whose components are of type reference. The index
            // must be of type int and value must be of type reference. The
            // arrayref, index, and value are popped from the operand stack. The
            // reference value is stored as the component of the array at index.
            {
                uint8_t index = code[pc+1];

                current_local_variables[index].type = _array;
                current_local_variables[index].value._array = pop_from_ostack(&(STACK->operand_stack))->operand.value._array;
            }
            pc += 2;
            break;

        case _istore_0:
        case _istore_1:
        case _istore_2:
        case _istore_3:
            // The <n> must be an index into the local variable array of the
            //  current frame (§2.6). The value on the top of the operand stack
            //  must be of type int. It is popped from the operand stack, and the
            //  value of the local variable at <n> is set to value.
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
            // Both <n> and <n>+1 must be indices into the local variable array
            // of the current frame (§2.6). The value on the top of the operand
            // stack must be of type long. It is popped from the operand stack,
            // and the local variables at <n> and <n>+1 are set to value.
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
            // The <n> must be an index into the local variable array of the
            // current frame (§2.6). The value on the top of the operand stack
            // must be of type float. It is popped from the operand stack and
            // undergoes value set conversion (§2.8.3), resulting in value'. The
            // value of the local variable at <n> is set to value'.
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
            // Both <n> and <n>+1 must be indices into the local variable array
            // of the current frame (§2.6). The value on the top of the operand
            // stack must be of type double. It is popped from the operand stack
            // and undergoes value set conversion (§2.8.3), resulting in value'.
            // The local variables at <n> and <n>+1 are set to value'
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
            // The <n> must be an index into the local variable array of the
            // current frame (§2.6). The objectref on the top of the operand stack
            // must be of type returnAddress or of type reference. It is popped
            // from the operand stack, and the value of the local variable at <n>
            // is set to objectref.
            {
                uint8_t index = code[pc] - _astore_0;

                current_local_variables[index].type = _array;
                current_local_variables[index].value._array = pop_from_ostack(&(STACK->operand_stack))->operand.value._array;
            }
            pc += 1;
            break;

        case _iastore:
            // The arrayref must be of type reference and must refer to an array
            // whose components are of type int. Both index and value must be
            // of type int. The arrayref, index, and value are popped from the
            // operand stack. The int value is stored as the component of the
            // array indexed by index
            {
                int value= pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int index = pop_from_ostack(&(STACK->operand_stack))->operand.value._int;

                int *array = (int *) pop_from_ostack(&(STACK->operand_stack))->operand.value._array;

                array[index] = value;
            }
            pc += 1;
            break;

        case _dup:
            // Duplicate the top value on the operand stack and push the
            // duplicated value onto the operand stack.
            // The dup instruction must not be used unless value is a value of a
            // category 1 computational type (§2.11.1).
            {
                vm_ostack_t *popped_operand = pop_from_ostack(&(STACK->operand_stack));
                push_into_ostack(&(STACK->operand_stack), &(popped_operand));
                push_into_ostack(&(STACK->operand_stack), &(popped_operand));
            }
            pc += 1;
            break;

        case _iadd:
            // Both value1 and value2 must be of type int. The values are popped
            // from the operand stack. The int result is value1 + value2. The
            // result is pushed onto the operand stack.
            // The result is the 32 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type int. If overflow occurs, then the sign of the result
            // may not be the same as the sign of the mathematical sum of the
            // two values.
            // Despite the fact that overflow may occur, execution of an iadd
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type long. The values are
            // popped from the operand stack. The long result is value1 + value2.
            // The result is pushed onto the operand stack.
            // The result is the 64 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type long. If overflow occurs, the sign of the result may
            // not be the same as the sign of the mathematical sum of the two
            // values.
            // Despite the fact that overflow may occur, execution of an ladd
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type float. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The float result is
            // value1' + value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type double. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The double result is
            // value1' + value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type int. The values are popped
            // from the operand stack. The int result is value1 - value2. The
            // result is pushed onto the operand stack.
            // For int subtraction, a-b produces the same result as a+(-b). For
            // int values, subtraction from zero is the same as negation.
            // The result is the 32 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type int. If overflow occurs, then the sign of the result
            // may not be the same as the sign of the mathematical difference of
            // the two values.
            // Despite the fact that overflow may occur, execution of an isub
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type long. The values are
            // popped from the operand stack. The long result is value1 - value2.
            // The result is pushed onto the operand stack.
            // For long subtraction, a-b produces the same result as a+(-b). For
            // long values, subtraction from zero is the same as negation.
            // The result is the 64 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type long. If overflow occurs, then the sign of the result
            // may not be the same as the sign of the mathematical difference of
            // the two values.
            // Despite the fact that overflow may occur, execution of an lsub
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type float. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The float result is
            // value1' - value2'. The result is pushed onto the operand stack.
            // For float subtraction, it is always the case that a-b produces
            // the same result as a+(-b). However, for the fsub instruction,
            // subtraction from zero is not the same as negation, because if x is
            // +0.0, then 0.0-x equals +0.0, but -x equals -0.0.
            // The Java Virtual Machine requires support of gradual underflow
            // as defined by IEEE 754. Despite the fact that overflow, underflow,
            // or loss of precision may occur, execution of an fsub instruction
            // never throws a run-time exception.
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
            // Both value1 and value2 must be of type double. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The double result is
            // value1' - value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type int. The values are popped
            // from the operand stack. The int result is value1 * value2. The
            // result is pushed onto the operand stack.
            // The result is the 32 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type int. If overflow occurs, then the sign of the result
            // may not be the same as the sign of the mathematical multiplication
            // of the two values.
            // Despite the fact that overflow may occur, execution of an imul
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type long. The values are
            // popped from the operand stack. The long result is value1 * value2.
            // The result is pushed onto the operand stack.
            // The result is the 64 low-order bits of the true mathematical result
            // in a sufficiently wide two's-complement format, represented as a
            // value of type long. If overflow occurs, the sign of the result may
            // not be the same as the sign of the mathematical multiplication of
            // the two values.
            // Despite the fact that overflow may occur, execution of an lmul
            // instruction never throws a run-time exception.
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
            // Both value1 and value2 must be of type float. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The float result is
            // value1' * value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type double. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The double result is
            // value1' * value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type int. The values are popped
            // from the operand stack. The int result is the value of the Java
            // programming language expression value1 / value2. The result is
            // pushed onto the operand stack.
            // An int division rounds towards 0; that is, the quotient produced
            // for int values in n/d is an int value q whose magnitude is as large
            // as possible while satisfying |d ⋅ q| ≤ |n|. Moreover, q is positive
            // when |n| ≥ |d| and n and d have the same sign, but q is negative
            // when |n| ≥ |d| and n and d have opposite signs.
            // There is one special case that does not satisfy this rule: if the
            // dividend is the negative integer of largest possible magnitude for
            // the int type, and the divisor is -1, then overflow occurs, and the
            // result is equal to the dividend. Despite the overflow, no exception
            // is thrown in this case.
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
            // Both value1 and value2 must be of type long. The values are
            // popped from the operand stack. The long result is the value of
            // the Java programming language expression value1 / value2. The
            // result is pushed onto the operand stack.
            // A long division rounds towards 0; that is, the quotient produced
            // for long values in n / d is a long value q whose magnitude is
            // as large as possible while satisfying |d ⋅ q| ≤ |n|. Moreover, q is
            // positive when |n| ≥ |d| and n and d have the same sign, but q is
            // negative when |n| ≥ |d| and n and d have opposite signs.
            // There is one special case that does not satisfy this rule: if the
            // dividend is the negative integer of largest possible magnitude for
            // the long type and the divisor is -1, then overflow occurs and the
            // result is equal to the dividend; despite the overflow, no exception
            // is thrown in this case.
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
            // Both value1 and value2 must be of type float. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The float result is
            // value1' / value2'. The result is pushed onto the operand stack.
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
            // Both value1 and value2 must be of type double. The values are
            // popped from the operand stack and undergo value set conversion
            // (§2.8.3), resulting in value1' and value2'. The double result is
            // value1' / value2'. The result is pushed onto the operand stack.
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

        case _return:
            // The current method must have return type void. If the
            // current method is a synchronized method, the monitor entered
            // or reentered on invocation of the method is updated and
            // possibly exited as if by execution of a monitorexit instruction
            // (§monitorexit) in the current thread. If no exception is thrown,
            // any values on the operand stack of the current frame (§2.6) are
            // discarded.
            // The interpreter then returns control to the invoker of the method,
            // reinstating the frame of the invoker.
            {
                vm_ostack_t *stack_frame = pop_from_ostack(&(STACK->operand_stack));
                vm_ostack_t *temp_stack;

                while(stack_frame != NULL)
                {
                    temp_stack = stack_frame;
                    stack_frame = stack_frame->next_frame;
                    free(temp_stack);
                }
            }
            pc += 1;
            break;

        case _getstatic:
            // The unsigned indexbyte1 and indexbyte2 are used to construct an
            // index into the run-time constant pool of the current class (§2.6),
            // where the value of the index is (indexbyte1 << 8) | indexbyte2.
            // The run-time constant pool item at that index must be a symbolic
            // reference to a field (§5.1), which gives the name and descriptor of
            // the field as well as a symbolic reference to the class or interface
            // in which the field is to be found. The referenced field is resolved
            // (§5.4.3.2).
            // On successful resolution of the field, the class or interface that
            // declared the resolved field is initialized (§5.5) if that class or
            // interface has not already been initialized.
            // The value of the class or interface field is fetched and pushed onto
            // the operand stack.
            {
                vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                new_operand_frame->operand.type = _string;
                new_operand_frame->operand.value._string = calloc(10, sizeof(char));
                new_operand_frame->next_frame = NULL;

                sprintf(new_operand_frame->operand.value._string, "getstatic");
                push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
            }
            pc += 3;
            break;

        case _invokevirtual:
        case _invokespecial:
            // jesus tenha piedade da minha menção
            {
                uint8_t indexbyte1 = code[pc+1];
                uint8_t indexbyte2 = code[pc+2];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;

                uint16_t class_index = current_constant_pool[index].info.methodref_info.class_index;
                uint16_t name_and_type_index = current_constant_pool[index].info.methodref_info.name_and_type_index;

                uint16_t class_name_index = current_constant_pool[class_index].info.class_info.name_index;
                uint16_t name_index = current_constant_pool[name_and_type_index].info.nameandtype_info.name_index;

                vm_utf8_t class_name = current_constant_pool[class_name_index].info.utf8_info;
                vm_utf8_t name = current_constant_pool[name_index].info.utf8_info;

                uint16_t *class_name_string = vm_utf8_to_uint16_t(class_name.length, class_name.bytes);
                uint16_t *name_string = vm_utf8_to_uint16_t(name.length, name.bytes);

                char class_name_buffer[class_name.length];
                char name_buffer[name.length];

                for (int j = 0; j < class_name.length; j++) {
                    sprintf(&(class_name_buffer[j]), "%lc", class_name_string[j]);
                }

                for (int j = 0; j < name.length; j++) {
                    sprintf(&(name_buffer[j]), "%lc", name_string[j]);
                }

                if (vm_strcmp(class_name_buffer, "java/io/PrintStream")) {
                    if (vm_strcmp(name_buffer, "print") || vm_strcmp(name_buffer, "println")) {
                        vm_ostack_t *popped_operand = pop_from_ostack(&(STACK->operand_stack));

                        char newline = vm_strcmp(name_buffer, "print") ? '\0' : '\n';

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
                    if (vm_strcmp(name_buffer, "<init>")) {
                        STACK->StringBuilder = realloc(STACK->StringBuilder, sizeof(char));
                        STACK->StringBuilder[0] = '\0';
                    } else if (vm_strcmp(name_buffer, "append")) {
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
                    } else if (vm_strcmp(name_buffer, "toString")) {
                        vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                        new_operand_frame->operand.type = _string;
                        new_operand_frame->operand.value._string = STACK->StringBuilder;
                        new_operand_frame->next_frame = NULL;

                        push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
                    }
                }
            }
            pc += 3;
            break;

        case _new:
            {
                vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                new_operand_frame->operand.type = _string;
                new_operand_frame->operand.value._string = calloc(4, sizeof(char));
                new_operand_frame->next_frame = NULL;

                sprintf(new_operand_frame->operand.value._string, "new");
                push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
            }
            pc += 3;
            break;

        case _invokedynamic:
            // Each specific lexical occurrence of an invokedynamic instruction
            // is called a dynamic call site.
            // First, the unsigned indexbyte1 and indexbyte2 are used to construct
            // an index into the run-time constant pool of the current class (§2.6),
            // where the value of the index is (indexbyte1 << 8) | indexbyte2.
            // The run-time constant pool item at that index must be a symbolic
            // reference to a call site specifier (§5.1). The values of the third and
            // fourth operand bytes must always be zero.
            pc += 5;
            break;

        case _newarray:
            // The count must be of type int. It is popped off the operand stack.
            // The count represents the number of elements in the array to be
            // created.
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

                vm_ostack_t *new_operand_frame = calloc(1, sizeof(vm_ostack_t));

                new_operand_frame->operand.type = _array;
                new_operand_frame->operand.value._array = array;
                new_operand_frame->next_frame = NULL;

                push_into_ostack(&(STACK->operand_stack), &(new_operand_frame));
            }
            pc += 2;
            break;

        case _wide:
            // The wide instruction modifies the behavior of another instruction.
            // It takes one of two formats, depending on the instruction being
            // modified. The first form of the wide instruction modifies one of the
            // instructions iload, fload, aload, lload, dload, istore, fstore, astore,
            // lstore, dstore, or ret (§iload, §fload, §aload, §lload, §dload,
            // §istore, §fstore, §astore, §lstore, §dstore, §ret). The second form
            // applies only to the iinc instruction (§iinc).
            // In either case, the wide opcode itself is followed in the compiled
            // code by the opcode of the instruction wide modifies. In either
            // form, two unsigned bytes indexbyte1 and indexbyte2 follow the
            // modified opcode and are assembled into a 16-bit unsigned index
            // to a local variable in the current frame (§2.6), where the value
            // of the index is (indexbyte1 << 8) | indexbyte2. The calculated
            // index must be an index into the local variable array of the current
            // frame. Where the wide instruction modifies an lload, dload, lstore,
            // or dstore instruction, the index following the calculated index
            // (index + 1) must also be an index into the local variable array. In
            // the second form, two immediate unsigned bytes constbyte1 and
            // constbyte2 follow indexbyte1 and indexbyte2 in the code stream.
            // Those bytes are also assembled into a signed 16-bit constant,
            // where the constant is (constbyte1 << 8) | constbyte2.
            // The widened bytecode operates as normal, except for the use of
            // the wider index and, in the case of the second form, the larger
            // increment range.
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
