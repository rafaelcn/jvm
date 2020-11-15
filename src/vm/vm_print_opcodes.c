#include <stdio.h>

#include "lib/vm_string.h"

#include "vm_opcodes.h"
#include "vm_print_opcodes.h"

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
            printf("putstatic\n");
            pc += 3;
            break;

        case _getfield:
            printf("getfield\n");
            pc += 3;
            break;

        case _putfield:
            printf("putfield\n");
            pc += 3;
            break;

        case _invokevirtual:
            printf("invokevirtual\n");
            pc += 3;
            break;

        case _invokespecial:
            printf("invokespecial\n");
            pc += 3;
            break;

        case _invokestatic:
            printf("invokestatic\n");
            pc += 3;
            break;

        case _invokeinterface:
            printf("invokeinterface\n");
            pc += 5;
            break;

        case _invokedynamic:
            printf("invokedynamic\n");
            pc += 5;
            break;

        case _new:
            printf("new\n");
            pc += 3;
            break;

        case _newarray:
            printf("newarray\n");
            pc += 2;
            break;

        case _anewarray:
            printf("anewarray\n");
            pc += 3;
            break;

        case _arraylength:
            printf("arraylength\n");
            pc += 1;
            break;

        case _athrow:
            printf("athrow\n");
            pc += 1;
            break;

        case _checkcast:
            printf("checkcast\n");
            pc += 3;
            break;

        case _instanceof:
            printf("instanceof\n");
            pc += 3;
            break;

        case _monitorenter:
            printf("monitorenter\n");
            pc += 1;
            break;

        case _monitorexit:
            printf("monitorexit\n");
            pc += 2;
            break;

        case _wide:
            _WIDE = 1;
            printf("wide\n");
            pc += 1;
            break;

        case _multianewarray:
            printf("multianewarray\n");
            pc += 4;
            break;

        case _ifnull:
            printf("ifnull\n");
            pc += 3;
            break;

        case _ifnonnull:
            printf("ifnonnull\n");
            pc += 3;
            break;

        case _goto_w:
            printf("goto_w\n");
            pc += 5;
            break;

        case _jsr_w:
            printf("jsr_w\n");
            pc += 5;
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

    vm_uint32_string_t *uint16_string;
    char *buffer = NULL;

    for (uint16_t i = 0; i < class_file.methods_count; i++) {
        method_name = class_file.constant_pool[class_file.methods[i].name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint32_t(method_name.length, method_name.bytes);

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
        uint16_string = vm_utf8_to_uint32_t(attribute_name.length, attribute_name.bytes);

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
