#ifndef TACS_H
#define	TACS_H

#include "hashtable.h"

#define TAC_SYMBOL			0
#define TAC_ADD				1
#define TAC_SUB				2
#define TAC_MUL				3
#define TAC_DIV				4
#define TAC_MOV				5
#define TAC_JZ				6
#define TAC_LABEL			7
#define TAC_FUNC_START 		8
#define TAC_FUNC_END 		9
#define TAC_FUNC_CALL 		10
#define TAC_PUSH_PARAM 		11
#define TAC_POP_PARAMS 		12
#define TAC_RETURN 			13
#define TAC_LE 				14
#define TAC_GE 				15
#define TAC_EQ 				16
#define TAC_NE 				17
#define TAC_OR 				18
#define TAC_AND 			19
#define TAC_GREATER 		20
#define TAC_LESS 			21
#define TAC_JMP				22
#define TAC_FUNC_RET		23
#define TAC_VEC_INI			24
#define TAC_POINTER_DECL	25
#define TAC_INPUT			26
#define TAC_OUTPUT			27
#define TAC_MOV_VEC			28
#define TAC_VEC_ACCESS		29
#define TAC_MINUS			30
#define TAC_DEREF			31
#define TAC_REF				32
#define TAC_REF_VEC			33

typedef struct tac_node {
	int type;
	Entry * target;
	Entry * op1;
	Entry * op2;
	struct tac_node * prev;
	//struct tac_node * next;	
} TAC;

TAC * tac_create(int tacType, Entry * target, Entry * src1, Entry * src2);

TAC * tac_join(TAC * first, TAC * last);

void tac_print_single(TAC * tac);

void tac_print_list(TAC * tac);

char * ttr(int value);

#endif	/* TACS_H */

