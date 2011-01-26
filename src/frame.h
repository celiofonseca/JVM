#ifndef FRAME_H
#define FRAME_H

#include "stack.h"
#include "types.h"
#include "carregador.h"
/**
 Frame. Modificar de void para os tipos corretos.
 */

struct frame 
{
	u4 *fields;
	void **constant_pool;
	u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 	*code;
	u4 pc;
};

/**
 Pilha de frame.
 */
struct frame_stack
{
	struct frame *value;
	struct frame_stack *next;
};

struct frame *current_frame;

void newFrame(void **constant_pool, Code_attribute *code_attribute);
void freeFrame();
 

#endif
