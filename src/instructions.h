#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "types.h"

/* TODO criei essa funcao para testes, pode deletar depois se quiserem*/
void execute_instruction(u1 opcode);

/* TO DO - Decidir onde o PC vai ficar (decidir o tipo também)*/
u8 pc;

/* Um array contendo ponteiros para as instruções */
void (*instr[256])();

/* Inicializa o array de instruções */
void initializeInstr();



/* As instruções possíveis */
void funct_nop();
void funct_aconst_null();
void funct_iconst_m1();
void funct_iconst_0();
void funct_iconst_1();
void funct_iconst_2();
void funct_iconst_3();
void funct_iconst_4();
void funct_iconst_5();
void funct_lconst_0();
void funct_lconst_1();
void funct_fconst_0();
void funct_fconst_1();
void funct_fconst_2();
void funct_dconst_0();
void funct_dconst_1();
void funct_bipush();
void funct_sipush();
void funct_ldc();
void funct_ldc_w();
void funct_ldc2_w();
void funct_iload();
void funct_lload();
void funct_fload();
void funct_dload();
void funct_aload();
void funct_iload_0();
void funct_iload_1();
void funct_iload_2();
void funct_iload_3();
void funct_lload_0();
void funct_lload_1();
void funct_lload_2();
void funct_lload_3();
void funct_fload_0();
void funct_fload_1();
void funct_fload_2();
void funct_fload_3();
void funct_dload_0();
void funct_dload_1();
void funct_dload_2();
void funct_dload_3();
void funct_aload_0();
void funct_aload_1();
void funct_aload_2();
void funct_aload_3();
void funct_iaload();
void funct_laload();
void funct_faload();
void funct_daload();
void funct_aaload();
void funct_baload();
void funct_caload();
void funct_saload();
void funct_istore();
void funct_lstore();
void funct_fstore();
void funct_dstore();
void funct_astore();
void funct_istore_0();
void funct_istore_1();
void funct_istore_2();
void funct_istore_3();
void funct_lstore_0();
void funct_lstore_1();
void funct_lstore_2();
void funct_lstore_3();
void funct_fstore_0();
void funct_fstore_1();
void funct_fstore_2();
void funct_fstore_3();
void funct_dstore_0();
void funct_dstore_1();
void funct_dstore_2();
void funct_dstore_3();
void funct_astore_0();
void funct_astore_1();
void funct_astore_2();
void funct_astore_3();
void funct_iastore();
void funct_lastore();
void funct_fastore();
void funct_dastore();
void funct_aastore();
void funct_bastore();
void funct_castore();
void funct_sastore();
void funct_pop();
void funct_pop2();
void funct_dup();
void funct_dup_x1();
void funct_dup_x2();
void funct_dup2();
void funct_dup2_x1();
void funct_dup2_x2();
void funct_swap();
void funct_iadd();
void funct_ladd();
void funct_fadd();
void funct_dadd();
void funct_isub();
void funct_lsub();
void funct_fsub();
void funct_dsub();
void funct_imul();
void funct_lmul();
void funct_fmul();
void funct_dmul();
void funct_idiv();
void funct_ldiv();
void funct_fdiv();
void funct_ddiv();
void funct_irem();
void funct_lrem();
void funct_frem();
void funct_drem();
void funct_ineg();
void funct_lneg();
void funct_fneg();
void funct_dneg();
void funct_ishl();
void funct_lshl();
void funct_ishr();
void funct_lshr();
void funct_iushr();
void funct_lushr();
void funct_iand();
void funct_land();
void funct_ior();
void funct_lor();
void funct_ixor();
void funct_lxor();
void funct_iinc();
void funct_i2l();
void funct_i2f();
void funct_i2d();
void funct_l2i();
void funct_l2f();
void funct_l2d();
void funct_f2i();
void funct_f2l();
void funct_f2d();
void funct_d2i();
void funct_d2l();
void funct_d2f();
void funct_i2b();
void funct_i2c();
void funct_i2s();
void funct_lcmp();
void funct_fcmpl();
void funct_fcmpg();
void funct_dcmpl();
void funct_dcmpg();
void funct_ifeq();
void funct_ifne();
void funct_iflt();
void funct_ifge();
void funct_ifgt();
void funct_ifle();
void funct_if_icmpeq();
void funct_if_icmpne();
void funct_if_icmplt();
void funct_if_icmpge();
void funct_if_icmpgt();
void funct_if_icmple();
void funct_if_acmpeq();
void funct_if_acmpne();
void funct_goto();
void funct_jsr();
void funct_ret();
void funct_tableswitch();
void funct_lookupswitch();
void funct_ireturn();
void funct_lreturn();
void funct_freturn();
void funct_dreturn();
void funct_areturn();
void funct_return();
void funct_getstatic();
void funct_putstatic();
void funct_getfield();
void funct_putfield();
void funct_invokevirtual();
void funct_invokespecial();
void funct_invokestatic();
void funct_invokeinterface();
/*void funct_nao_utilizada;*/
void funct_new();
void funct_newarray();
void funct_anewarray();
void funct_arraylength();
void funct_athrow();
void funct_checkcast();
void funct_instanceof();
void funct_monitorenter();
void funct_monitorexit();
void funct_wide();
void funct_multianewarray();
void funct_ifnull();
void funct_ifnonnull();
void funct_goto_w();
void funct_jsr_w();

#endif /* INSTRUCTIONS_H_ */
