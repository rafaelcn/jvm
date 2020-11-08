#include <stdio.h>
#include <stdlib.h>

#include "vm_opcodes.h"

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

uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK) {
    uint8_t _WIDE = 0;

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
            //push(code[pc] - 0x03);
            pc += 1;
            break;

        case _ldc:
            {
                uint8_t index = code[pc+1];

                switch (STACK->top_frame->constant_pool[index].tag) {
                case 3: // Integer
                    {
                        int _i = STACK->top_frame->constant_pool[index].info.integer_info.bytes;

                        vm_local_variable_item_t *new_item = calloc(1, sizeof (vm_local_variable_item_t));
                        new_item->value._float = (float) _i;
                        new_item->next_item = NULL;

                        vm_local_variable_item_t *current_item = STACK->top_frame->local_variables_list->first_item;

                        STACK->top_frame->local_variables_list->local_variables_count += 1;
                        if (current_item == NULL) {
                            current_item = new_item;
                        } else {
                            while (current_item->next_item != NULL)
                            {
                                current_item = current_item->next_item;
                            }

                            current_item->next_item = new_item;
                        }
                    }
                    break;

                case 4: // Float
                    {
                        float _f = STACK->top_frame->constant_pool[index].info.float_info.bytes;

                        vm_local_variable_item_t *new_item = calloc(1, sizeof (vm_local_variable_item_t));
                        new_item->value._float = _f;
                        new_item->next_item = NULL;

                        vm_local_variable_item_t *current_item = STACK->top_frame->local_variables_list->first_item;

                        STACK->top_frame->local_variables_list->local_variables_count += 1;
                        if (current_item == NULL) {
                            current_item = new_item;
                        } else {
                            while (current_item->next_item != NULL)
                            {
                                current_item = current_item->next_item;
                            }

                            current_item->next_item = new_item;
                        }
                    }
                    break;

                default:
                    break;
                }
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
            uint16_t local_variable_index = code[pc] - 0x1a;
            vm_local_variable_item_t *local_variable_item = STACK->top_frame->local_variables_list->first_item;
            
            for(uint16_t j = 0; j < local_variable_index; j++)
            {
                local_variable_item = local_variable_item->next_item;
            }
            vm_operand_stack_frame_t *new_operand_frame = calloc(
                1, sizeof (vm_operand_stack_frame_t));
            
            new_operand_frame->value._int = local_variable_item->value._int;
            push_into_ostack(STACK->top_frame->operand_stack, new_operand_frame);
            pc++;
            break;
        case _istore_0:
        case _istore_2:
        case _istore_1:
        case _istore_3:
            {
                // The <n> must be an index into the local variable array of the
                //  current frame (§2.6). The value on the top of the operand stack
                //  must be of type int. It is popped from the operand stack, and the
                //  value of the local variable at <n> is set to value.
                uint16_t local_variable_index = code[pc] - 0x3b;
                vm_local_variable_item_t *local_variable_item = STACK->top_frame->local_variables_list->first_item;
                vm_operand_stack_frame_t *stack_frame = pop_from_ostack(STACK->top_frame->operand_stack);

                for(uint16_t j = 0; j < local_variable_index; j++) {
                    local_variable_item = local_variable_item->next_item;
                }
                local_variable_item->value._int = stack_frame->value._int;
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
            vm_operand_stack_frame_t* first_stack_frame = pop_from_ostack(
                STACK->top_frame->operand_stack);
            vm_operand_stack_frame_t* second_stack_frame = pop_from_ostack(
                STACK->top_frame->operand_stack);
            vm_operand_stack_frame_t * result_frame = calloc(
                1, sizeof (vm_operand_stack_frame_t));
            
            result_frame->value._int = first_stack_frame->value._int +\
                second_stack_frame->value._int;
            push_into_ostack(STACK->top_frame->operand_stack, result_frame);
            pc++;
            break;
        case _return:
            {
                // The current method must have return type void. If the
                // current method is a synchronized method, the monitor entered
                // or reentered on invocation of the method is updated and
                // possibly exited as if by execution of a monitorexit instruction
                // (§monitorexit) in the current thread. If no exception is thrown,
                // any values on the operand stack of the current frame (§2.6) are
                // discarded.
                // The interpreter then returns control to the invoker of the method,
                // reinstating the frame of the invoker.
                vm_operand_stack_frame_t* stack_frame = pop_from_ostack(STACK->top_frame->operand_stack);
                vm_operand_stack_frame_t* temp_stack;
                
                while(stack_frame != NULL)
                {
                    temp_stack = stack_frame;
                    stack_frame = stack_frame->next_frame;
                    free(temp_stack);
                }
                pc += 1;
                break;
            }
        case _getstatic:
            {
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
                uint8_t indexbyte1 = code[pc+1];
                uint8_t indexbyte2 = code[pc+2];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;
                // TO DO
                pc += 3;
                break;
            }

        case _wide:
            _WIDE = 1;
            pc++;

        default:
            pc += 1;
            break;
        }
    }

    return pc;
}
