#include "astree.h"

#ifndef GENCODE_H
#define	GENCODE_H

extern Hashtable *hashtable;

TAC * generateCode(ASTREE * node);

TAC * make_binop(TAC * tac0, TAC * tac1, int type);

TAC * make_if_then(TAC * tac_exp, TAC * tac_cmd);

TAC * make_if_then_else(TAC * tac_exp, TAC * tac_cmd_if, TAC * tac_cmd_else);

TAC * make_loop(TAC * tac_exp, TAC * tac_cmd);

TAC * makeFuncDecl(TAC * identifier, TAC * declList, TAC * cmdBlock);

TAC * makeFuncFunCall(TAC * identifier, TAC * arguments);

TAC * makeFuncParams(ASTREE *node);

TAC * makeResult(TAC * retValue);

TAC * makeArrayDecl(TAC * identifier, TAC * index, TAC * iniList);

TAC * makePointerDecl(TAC * identifier, TAC * value);

TAC * makeInput(TAC * identifier);

TAC * makeOutput(TAC * exp, TAC * outList);

TAC * make_VectAss(TAC * identifier, TAC * indexExp, TAC * exp);

TAC * make_VectAccess(TAC * identifier, TAC * exp);

TAC *  makeRefAraay(TAC * identifier, TAC * exp);

#endif	/* GENCODE_H */
