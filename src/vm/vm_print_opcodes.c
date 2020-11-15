#include <stdio.h>

#include "vm_print_opcodes.h"
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

uint32_t vm_print_opcodes_helper(uint8_t *code, uint32_t pc) {
    uint8_t _WIDE = 0;

    for (uint8_t i = 0; i <= _WIDE; i++) {
        switch (code[pc]) {
        case _nop:
            printf("nop\n");
            pc += 1;
            break;

        case _aconst_null:
            printf("aconst_null\n");
            pc += 1;
            break;

        case _iconst_m1:
            printf("iconst_m1\n");
            pc += 1;
            break;

        case _iconst_0:
        case _iconst_1:
        case _iconst_2:
        case _iconst_3:
        case _iconst_4:
        case _iconst_5:
            printf("iconst_%i\n", code[pc] - _iconst_0);
            pc += 1;
            break;

        case _lconst_0:
        case _lconst_1:
            printf("lconst_%i\n", code[pc] - _lconst_0);
            pc += 1;
            break;

        case _fconst_0:
        case _fconst_1:
        case _fconst_2:
            printf("fconst_%i\n", code[pc] - _fconst_0);
            pc += 1;
            break;

        case _dconst_0:
        case _dconst_1:
            printf("dconst_%i\n", code[pc] - _dconst_0);
            pc += 1;
            break;

        case _bipush:
            printf("bipush\n");
            pc += 2;
            break;

        case _sipush:
            printf("sipush\n");
            pc += 2;
            break;

        case _ldc:
            printf("ldc\n");
            pc += 2;
            break;

        case _ldc_w:
            printf("ldc_w\n");
            pc += 3;
            break;

        case _ldc2_w:
            printf("ldc2_w\n");
            pc += 3;
            break;

        case _iload:
            printf("iload\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _lload:
            printf("lload\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _fload:
            printf("fload\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _dload:
            printf("dload\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _aload:
            printf("aload\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _iload_0:
        case _iload_1:
        case _iload_2:
        case _iload_3:
            printf("iload_%i\n", code[pc] - _iload_0);
            pc += 1;
            break;

        case _lload_0:
        case _lload_1:
        case _lload_2:
        case _lload_3:
            printf("lload_%i\n", code[pc] - _lload_0);
            pc += 1;
            break;

        case _fload_0:
        case _fload_1:
        case _fload_2:
        case _fload_3:
            printf("fload_%i\n", code[pc] - _fload_0);
            pc += 1;
            break;

        case _dload_0:
        case _dload_1:
        case _dload_2:
        case _dload_3:
            printf("dload_%i\n", code[pc] - _dload_0);
            pc += 1;
            break;

        case _aload_0:
        case _aload_1:
        case _aload_2:
        case _aload_3:
            printf("aload_%i\n", code[pc] - _aload_0);
            pc += 1;
            break;

        case _iaload:
            printf("iaload\n");
            pc += 1;
            break;

        case _laload:
            printf("laload\n");
            pc += 1;
            break;

        case _faload:
            printf("faload\n");
            pc += 1;
            break;

        case _daload:
            printf("daload\n");
            pc += 1;
            break;

        case _aaload:
            printf("aaload\n");
            pc += 1;
            break;

        case _baload:
            printf("baload\n");
            pc += 1;
            break;

        case _caload:
            printf("caload\n");
            pc += 1;
            break;

        case _saload:
            printf("saload\n");
            pc += 1;
            break;

        case _istore:
            printf("istore\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _lstore:
            printf("lstore\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _fstore:
            printf("fstore\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _dstore:
            printf("dstore\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _astore:
            printf("astore\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _istore_0:
        case _istore_1:
        case _istore_2:
        case _istore_3:
            printf("istore_%i\n", code[pc] - _istore_0);
            pc += 1;
            break;

        case _lstore_0:
        case _lstore_1:
        case _lstore_2:
        case _lstore_3:
            printf("lstore_%i\n", code[pc] - _lstore_0);
            pc += 1;
            break;

        case _fstore_0:
        case _fstore_1:
        case _fstore_2:
        case _fstore_3:
            printf("fstore_%i\n", code[pc] - _fstore_0);
            pc += 1;
            break;

        case _dstore_0:
        case _dstore_1:
        case _dstore_2:
        case _dstore_3:
            printf("dstore_%i\n", code[pc] - _dstore_0);
            pc += 1;
            break;

        case _astore_0:
        case _astore_1:
        case _astore_2:
        case _astore_3:
            printf("astore_%i\n", code[pc] - _astore_0);
            pc += 1;
            break;

        case _iastore:
            printf("iastore\n");
            pc += 1;
            break;

        case _lastore:
            printf("lastore\n");
            pc += 1;
            break;

        case _fastore:
            printf("fastore\n");
            pc += 1;
            break;

        case _dastore:
            printf("dastore\n");
            pc += 1;
            break;

        case _aastore:
            printf("aastore\n");
            pc += 1;
            break;

        case _bastore:
            printf("bastore\n");
            pc += 1;
            break;

        case _castore:
            printf("castore\n");
            pc += 1;
            break;

        case _sastore:
            printf("sastore\n");
            pc += 1;
            break;

        case _pop:
            printf("pop\n");
            pc += 1;
            break;

        case _pop2:
            printf("pop2\n");
            pc += 1;
            break;

        case _dup:
            printf("dup\n");
            pc += 1;
            break;

        case _dup_x1:
            printf("dup_x1\n");
            pc += 1;
            break;

        case _dup_x2:
            printf("dup_x2\n");
            pc += 1;
            break;

        case _dup2:
            printf("dup2\n");
            pc += 1;
            break;

        case _dup2_x1:
            printf("dup2_x1\n");
            pc += 1;
            break;

        case _dup2_x2:
            printf("dup2_x2\n");
            pc += 1;
            break;

        case _swap:
            printf("swap\n");
            pc += 1;
            break;

        case _iadd:
            printf("iadd\n");
            pc += 1;
            break;

        case _ladd:
            printf("ladd\n");
            pc += 1;
            break;

        case _fadd:
            printf("fadd\n");
            pc += 1;
            break;

        case _dadd:
            printf("dadd\n");
            pc += 1;
            break;

        case _isub:
            printf("isub\n");
            pc += 1;
            break;

        case _lsub:
            printf("lsub\n");
            pc += 1;
            break;

        case _fsub:
            printf("fsub\n");
            pc += 1;
            break;

        case _dsub:
            printf("dsub\n");
            pc += 1;
            break;

        case _imul:
            printf("imul\n");
            pc += 1;
            break;

        case _lmul:
            printf("lmul\n");
            pc += 1;
            break;

        case _fmul:
            printf("fmul\n");
            pc += 1;
            break;

        case _dmul:
            printf("dmul\n");
            pc += 1;
            break;

        case _idiv:
            printf("idiv\n");
            pc += 1;
            break;

        case _ldiv:
            printf("ldiv\n");
            pc += 1;
            break;

        case _fdiv:
            printf("fdiv\n");
            pc += 1;
            break;

        case _ddiv:
            printf("ddiv\n");
            pc += 1;
            break;

        case _irem:
            printf("irem\n");
            pc += 1;
            break;

        case _lrem:
            printf("lrem\n");
            pc += 1;
            break;

        case _frem:
            printf("frem\n");
            pc += 1;
            break;

        case _drem:
            printf("drem\n");
            pc += 1;
            break;

        case _ineg:
            printf("ineg\n");
            pc += 1;
            break;

        case _lneg:
            printf("lneg\n");
            pc += 1;
            break;

        case _fneg:
            printf("fneg\n");
            pc += 1;
            break;

        case _dneg:
            printf("dneg\n");
            pc += 1;
            break;

        case _ishl:
            printf("ishl\n");
            pc += 1;
            break;

        case _lshl:
            printf("lshl\n");
            pc += 1;
            break;

        case _ishr:
            printf("ishr\n");
            pc += 1;
            break;

        case _lshr:
            printf("lshr\n");
            pc += 1;
            break;

        case _iushr:
            printf("iushr\n");
            pc += 1;
            break;

        case _lushr:
            printf("lushr\n");
            pc += 1;
            break;

        case _iand:
            printf("iand\n");
            pc += 1;
            break;

        case _land:
            printf("land\n");
            pc += 1;
            break;

        case _ior:
            printf("ior\n");
            pc += 1;
            break;

        case _lor:
            printf("lor\n");
            pc += 1;
            break;

        case _ixor:
            printf("ixor\n");
            pc += 1;
            break;

        case _lxor:
            printf("lxor\n");
            pc += 1;
            break;

        case _iinc:
            printf("iinc\n");
            pc += 3;
            break;

        case _i2l:
            printf("i2l\n");
            pc += 1;
            break;

        case _i2f:
            printf("i2f\n");
            pc += 1;
            break;

        case _i2d:
            printf("i2d\n");
            pc += 1;
            break;

        case _l2i:
            printf("l2i\n");
            pc += 1;
            break;

        case _l2f:
            printf("l2f\n");
            pc += 1;
            break;

        case _l2d:
            printf("l2d\n");
            pc += 1;
            break;

        case _f2i:
            printf("f2i\n");
            pc += 1;
            break;

        case _f2l:
            printf("f2l\n");
            pc += 1;
            break;

        case _f2d:
            printf("f2d\n");
            pc += 1;
            break;

        case _d2i:
            printf("d2i\n");
            pc += 1;
            break;

        case _d2l:
            printf("d2l\n");
            pc += 1;
            break;

        case _d2f:
            printf("d2f\n");
            pc += 1;
            break;

        case _i2b:
            printf("i2b\n");
            pc += 1;
            break;

        case _i2c:
            printf("i2c\n");
            pc += 1;
            break;

        case _i2s:
            printf("i2s\n");
            pc += 1;
            break;

        case _lcmp:
            printf("lcmp\n");
            pc += 1;
            break;

        case _fcmpl:
            printf("fcmpl\n");
            pc += 1;
            break;

        case _fcmpg:
            printf("fcmpg\n");
            pc += 1;
            break;

        case _dcmpl:
            printf("dcmpl\n");
            pc += 1;
            break;

        case _dcmpg:
            printf("dcmpg\n");
            pc += 1;
            break;

        case _ifeq:
            printf("ifeq\n");
            pc += 3;
            break;

        case _ifne:
            printf("ifne\n");
            pc += 3;
            break;

        case _iflt:
            printf("iflt\n");
            pc += 3;
            break;

        case _ifge:
            printf("ifge\n");
            pc += 3;
            break;

        case _ifgt:
            printf("ifgt\n");
            pc += 3;
            break;

        case _ifle:
            printf("ifle\n");
            pc += 3;
            break;

        case _if_icmpeq:
            printf("if_icmpeq\n");
            pc += 3;
            break;

        case _if_icmpne:
            printf("if_icmpne\n");
            pc += 3;
            break;

        case _if_icmplt:
            printf("if_icmplt\n");
            pc += 3;
            break;

        case _if_icmpge:
            printf("if_icmpge\n");
            pc += 3;
            break;

        case _if_icmpgt:
            printf("if_icmpgt\n");
            pc += 3;
            break;

        case _if_icmple:
            printf("if_icmple\n");
            pc += 3;
            break;

        case _if_acmpeq:
            printf("if_acmpeq\n");
            pc += 3;
            break;

        case _if_acmpne:
            printf("if_acmpne\n");
            pc += 3;
            break;

        case _goto:
            printf("goto\n");
            pc += 3;
            break;

        case _jsr:
            printf("jsr\n");
            pc += 3;
            break;

        case _ret:
            printf("ret\n");
            if (_WIDE) {
                pc += 3;
            } else {
                pc += 2;
            }
            break;

        case _tableswitch:
            printf("tableswitch\n");
            break;

        case _lookupswitch:
            printf("lookupswitch\n");
            break;

        case _ireturn:
            printf("ireturn\n");
            pc = 0xFFFFFFFF;
            break;

        case _lreturn:
            printf("lreturn\n");
            pc = 0xFFFFFFFF;
            break;

        case _freturn:
            printf("freturn\n");
            pc = 0xFFFFFFFF;
            break;

        case _dreturn:
            printf("dreturn\n");
            pc = 0xFFFFFFFF;
            break;

        case _areturn:
            printf("areturn\n");
            pc = 0xFFFFFFFF;
            break;

        case _return:
            printf("return\n");
            pc = 0xFFFFFFFF;
            break;

        case _getstatic:
            printf("getstatic\n");
            pc += 3;
            break;

        case _putstatic:
        case _getfield:
        case _putfield:

        case _invokevirtual:
            printf("invokevirtual\n");
            pc += 3;
            break;

        case _invokespecial:
            printf("invokespecial\n");
            pc += 3;
            break;

        case _new:
            printf("new\n");
            pc += 3;
            break;

        case _invokedynamic:
            printf("invokedynamic\n");
            pc += 5;
            break;

        case _newarray:
            printf("newarray\n");
            pc += 2;
            break;

        case _wide:
            _WIDE = 1;
            printf("wide\n");
            pc += 1;
            break;

        default:
            printf("unkown instruction\n");
            pc += 1;
            break;
        }
    }

    return pc;
}

void vm_print_opcodes(vm_class_file_t class_file) {
    printf("MAIN (OPCODES)\n");
    printf("----------------\n\n");

    // finding the main
    vm_method_info_t *main_method = calloc(1, sizeof (vm_method_info_t));
    vm_utf8_t method_name;

    vm_uint16_string_t *uint16_string;
    char *buffer = NULL;

    for (uint16_t i = 0; i < class_file.methods_count; i++) {
        method_name = class_file.constant_pool[class_file.methods[i].name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint16_t(method_name.length, method_name.bytes);

        buffer = realloc(buffer, ((uint16_string->length) * sizeof(char)));

        // first we print the name of the method to a buffer
        for (int j = 0; j < uint16_string->length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string->string[j]);
        }

        // after that we check if the name is 'main'
        if (vm_strcmp(buffer, "main")) {
            // on success we save a reference to that method
            main_method = &(class_file.methods[i]);
            // and quit the loop
            break;
        } else {
            // if the method isn't the main method we set it to NULL
            main_method = NULL;
        }
    }

    // Check if we could find a main method
    if (main_method == NULL) {
        // Finishes the execution if we couldn't
        printf("Couldn't find a main method\n");
    }

    // looking for the main code
    vm_code_t *main_code = calloc(1, sizeof (vm_code_t));
    vm_utf8_t attribute_name;

    for (uint16_t i = 0; i < main_method->attributes_count; i++) {
        attribute_name = class_file.constant_pool[main_method->attributes[i].attribute_name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint16_t(attribute_name.length, attribute_name.bytes);

        buffer = realloc(buffer, ((uint16_string->length) * sizeof(char)));

        // first we print the name of the method to a buffer
        for (int j = 0; j < uint16_string->length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string->string[j]);
        }

        if (vm_strcmp(buffer, "Code")) {
            main_code = &(main_method->attributes[i].info.code_attribute);
            break;
        } else {
            main_code = NULL;
        }
    }

    if (main_code == NULL) {
        printf("Couldn't find the code attribute of the main method\n");
    }

    for (uint32_t pc = 0; pc < main_code->code_length;) {
        pc = vm_print_opcodes_helper(main_code->code, pc);
    }

    printf("\n\n");
}
