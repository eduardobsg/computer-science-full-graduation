#include <stdio.h>
#include "tac.h"

/*
 *
 */
TAC * tac_create(int tacType, Entry * target, Entry * src1, Entry * src2)
{
    TAC *tac;

    tac = (TAC *) calloc(1, sizeof (TAC));
    tac->type = tacType;
    tac->target = target;
    tac->op1 = src1;
    tac->op2 = src2;
    tac->prev = NULL;
    //tac->next = NULL;	

    return tac;
}

/**
 * Concatenate lists of TACS
 * 
 * FIRST: in the normal flow of code,
 * it appears in the top<br />
 * LAST: in the normal flow of code,
 * it appears in the bottom
 * 
 * The nodes always point to previous,
 * so the concatenation goes like<br />
 * LASTLIST -> FIRSTLIST
 * 
 * @param first
 * @param last
 * @return a list like last->first
 */
TAC * tac_join(TAC * first, TAC * last)
{
    // |                |
    // FIRST            LAST

    TAC * tac;
    if (!first) return last;
    if (!last) return first;

    // |                   |
    // FIRST            LAST
    for (tac = last; tac->prev; tac = tac->prev)
        ; // reaches last node of the last queue

    //    |             |
    // LAST      ->     FIRST
    tac->prev = first; // puts LAST "under" FIRST

    return last;
}

/*
 *
 */
void tac_print_single(TAC * tac)
{
    if (tac->type == TAC_SYMBOL)
        return;

    fprintf(stderr, "[%15s, ", ttr(tac->type));
    fprintf(stderr, " %7s", tac->target ? tac->target->text : "      _");
    fprintf(stderr, ", %7s", tac->op1 ? tac->op1->text : "      _");
    fprintf(stderr, ", %7s", tac->op2 ? tac->op2->text : "      _");
    fprintf(stderr, "]");

    /*
    if (tac->prev)
        fprintf(stderr, " -> %s", ttr(tac->prev->type));
     */

    fprintf(stderr, "\n");
}

/*
 *
 */
void tac_print_list(TAC * tac)
{
    if (!tac) {
        fprintf(stderr, "\nTAC - instruction order:\n");
        return;
    }

    tac_print_list(tac->prev);
    tac_print_single(tac);
}

/**
 * Values translator
 * @param value
 * @return associated string
 */
char * ttr(int value)
{
    switch (value) {
    case TAC_SYMBOL: return "TAC_SYMBOL";
    case TAC_ADD: return "TAC_ADD";
    case TAC_SUB: return "TAC_SUB";
    case TAC_MUL: return "TAC_MUL";
    case TAC_DIV: return "TAC_DIV";
    case TAC_MOV: return "TAC_MOV";
    case TAC_JZ: return "TAC_JZ";
    case TAC_LABEL: return "TAC_LABEL";
    case TAC_FUNC_START: return "TAC_FUNC_START";
    case TAC_FUNC_END: return "TAC_FUNC_END";
    case TAC_FUNC_CALL: return "TAC_FUNC_CALL";
    case TAC_PUSH_PARAM: return "TAC_PUSH_PARAM";
    case TAC_POP_PARAMS: return "TAC_POP_PARAMS";
    case TAC_RETURN: return "TAC_RETURN";
    case TAC_LE: return "TAC_LE";
    case TAC_GE: return "TAC_GE";
    case TAC_EQ: return "TAC_EQ";
    case TAC_NE: return "TAC_NE";
    case TAC_OR: return "TAC_OR";
    case TAC_AND: return "TAC_AND";
    case TAC_GREATER: return "TAC_GREATER";
    case TAC_LESS: return "TAC_LESS";
    case TAC_JMP: return "TAC_JMP";
    case TAC_FUNC_RET: return "TAC_FUNC_RET";
    case TAC_VEC_INI: return "TAC_VEC_INI";
	case TAC_POINTER_DECL: return "TAC_POINTER_DECL";
	case TAC_INPUT: return "TAC_INPUT";
	case TAC_OUTPUT: return "TAC_OUTPUT";
	case TAC_MOV_VEC: return "TAC_MOV_VEC";
	case TAC_VEC_ACCESS: return "TAC_VEC_ACCESS";
	case TAC_MINUS: return "TAC_MINUS";
	case TAC_DEREF: return "TAC_DEREF";
	case TAC_REF: return "TAC_REF";
	case TAC_REF_VEC: return "TAC_REF_VEC";
    default: return "TAC_UNKNOWN";
    }
}
