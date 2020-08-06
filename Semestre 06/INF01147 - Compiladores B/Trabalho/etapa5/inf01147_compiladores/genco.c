#include <stdio.h>

#include "tac.h"
#include "hashtable.h"
#include "genco.h"

/*
 *
 */
TAC * generateCode(ASTREE * node)
{
    int i;
    TAC * code[MAX_SONS];
    TAC * result;

    if (!node)
        return 0;

    // PROCESS CHILDREN FIRST RECURSYVELLY
    for (i = 0; i < MAX_SONS; i++)
        if (node->son[i])
            code[i] = generateCode(node->son[i]);
        else
            code[i] = 0;

    switch (node->nodeType) {
    case ASTREE_PROGRAM: result = code[0];
        break;
    case ASTREE_DECL: result = tac_join(code[0], code[1]);
        break;
    case ASTREE_SIMPLE_DECL: result = make_binop(code[0], code[1], TAC_MOV);
        break;
	case ASTREE_ARRAY_DECL_INI:            
	case ASTREE_ARRAY_DECL: result = makeArrayDecl(code[0], code[1], code[2]);
		break;
	case ASTREE_ARRAY_DECL_LITS: result = tac_join(code[1], code[0]);	
		break;
	case ASTREE_POINTER_DECL: result = makePointerDecl(code[0], code[1]);
		break; 
    case ASTREE_FUNC: result = tac_join(code[0], code[1]);
        break;        
    case ASTREE_FUNC1: result = makeFuncDecl(code[0], code[2], code[3]);
        break;
    case ASTREE_FUNC2: result = makeFuncDecl(code[0], code[1], code[2]);
        break;
    case ASTREE_FUNC3: result = makeFuncDecl(code[0], NULL, code[2]);
        break;
    case ASTREE_FUNC4: result = makeFuncDecl(code[0], NULL, code[1]);
        break;
    case ASTREE_CMD_BLOCK: result = code[0];
        break;
    case ASTREE_CMDL: result = tac_join(code[0], code[1]);
        break;
    case ASTREE_FUNC_DECL: result = tac_join(code[0], code[1]);
        break;
    case ASTREE_FUNC_CALL: result = makeFuncFunCall(code[0], code[1]);
        break;
    case ASTREE_FUNC_CALL_LIST: result = makeFuncParams(node);
        break;
    case ASTREE_RETURN: result = makeResult(code[0]);
        break;
    case ASTREE_ADD: result = make_binop(code[0], code[1], TAC_ADD);
        break;
    case ASTREE_SUB: result = make_binop(code[0], code[1], TAC_SUB);
        break;
    case ASTREE_MUL: result = make_binop(code[0], code[1], TAC_MUL);
        break;
    case ASTREE_DIV: result = make_binop(code[0], code[1], TAC_DIV);
        break;
    case ASTREE_OPERATOR_LE: result = make_binop(code[0], code[1], TAC_LE);
        break;
    case ASTREE_OPERATOR_GE: result = make_binop(code[0], code[1], TAC_GE);
        break;
    case ASTREE_OPERATOR_EQ: result = make_binop(code[0], code[1], TAC_EQ);
        break;
    case ASTREE_OPERATOR_NE: result = make_binop(code[0], code[1], TAC_NE);
        break;
    case ASTREE_OPERATOR_OR: result = make_binop(code[0], code[1], TAC_OR);
        break;
    case ASTREE_OPERATOR_AND: result = make_binop(code[0], code[1], TAC_AND);
        break;
    case ASTREE_OPERATOR_GREATER: result = make_binop(code[0], code[1], TAC_GREATER);
        break;
    case ASTREE_OPERATOR_LESS: result = make_binop(code[0], code[1], TAC_LESS);
        break;
    case ASTREE_SYMBOL: result = tac_create(TAC_SYMBOL, node->symbol, NULL, NULL);
        break;
    case ASTREE_SCALA_ASS: result = make_binop(code[0], code[1], TAC_MOV);
        break;
    case ASTREE_VECT_SCALA_ASS: result = make_VectAss(code[0], code[1], code[2]);
        break;
	case ASTREE_VECT_ACCESS: result = make_VectAccess(code[0], code[1]);
		break;        
    case ASTREE_IF: result = make_if_then(code[0], code[1]);
        break;
    case ASTREE_IF_ELSE: result = make_if_then_else(code[0], code[1], code[2]);
        break;
    case ASTREE_LOOP: result = make_loop(code[0], code[1]);
        break;
    case ASTREE_INPUT: result = makeInput(code[0]);
    	break;
    case ASTREE_OUTPUT: result = code[0];
    	break;
    case ASTREE_OUTPUT_LIST: result = makeOutput(code[0], code[1]); 
        break;
    case ASTREE_UNARY_MINUS: result = tac_create(TAC_MINUS, makeTemp(), code[0]->target, NULL);
    	break;
	case ASTREE_POINTER_DEREFERENCE: result = tac_create(TAC_DEREF, makeTemp(), code[0]->target, NULL);
		break;
    case ASTREE_EXP_PARENTESIS: result = code[0];
    	break;
    case ASTREE_POINTER_REFERENCE: result = tac_create(TAC_REF, makeTemp(), code[0]->target, NULL);
    	break;
    case ASTREE_POINTER_REFERENCE_ARRAY: result = makeRefAraay(code[0], code[1]);
    	break;
        
    default:
        //fprintf(stderr, "Genco::generateCode() NOT IMPLEMENTED YET\n");
        result = 0;
    }

    return result;
}

TAC * make_binop(TAC * tac0, TAC * tac1, int type)
{
    TAC * result = NULL;

    if (type == TAC_MOV)
        result = tac_create(type, tac0->target, tac1->target, NULL);
    else
        result = tac_create(type, makeTemp(), tac0->target, tac1->target);

    return tac_join(tac0, tac_join(tac1, result));
}

/**
 * IF (tac_exp) THEN tac_cmd
 * @param tac_exp
 * @param tac_cmd
 * @return 
 */
TAC * make_if_then(TAC * tac_exp, TAC * tac_cmd)
{
    TAC * newJZ;
    TAC * newThen;

    Entry * labelDest = makeLabel();
    newJZ = tac_create(TAC_JZ, tac_exp ? tac_exp->target : NULL, labelDest, NULL);
    newThen = tac_create(TAC_LABEL, labelDest, NULL, NULL);

	// exp
    // JZ
    //  conditional command
    // label
    // ... normal code    
    
    return tac_join(tac_join(tac_exp, newJZ), tac_join(tac_cmd, newThen));
}

/**
 * IF (tac_exp) THEN tac_cmd_if ELSE cmd_else
 * @param tac_exp
 * @param tac_cmd_if
 * @param cmd_else
 * @return 
 */
TAC * make_if_then_else(TAC * tac_exp, TAC * tac_cmd_if, TAC * tac_cmd_else)
{
    // BASIC IDEA
    // JZ label_else            | B00   | RES
    //  cmd_if          | B0    |       |
    //  jmp label_end   |       |       |
    //                                  |
    // label_else       | B1    | B11   |
    //  cmd_else        |       |       |
    //                          |       |
    // label_end                |       |

    // Create tac's
    TAC * label_else, * label_end, * jmp_end, * jz_else;

    label_end = tac_create(TAC_LABEL, makeLabel(), NULL, NULL);
    jmp_end = tac_create(TAC_JMP, label_end ? label_end->target : NULL, NULL, NULL);

    label_else = tac_create(TAC_LABEL, makeLabel(), NULL, NULL);
    jz_else = tac_create(TAC_JZ, tac_exp ? tac_exp->target : NULL, label_else ? label_else->target : NULL, NULL);

    // JOINS
    TAC * b0 = tac_join(tac_cmd_if, jmp_end);
    TAC * b00 = tac_join(tac_exp, tac_join(jz_else, b0));

    TAC * b1 = tac_join(label_else, tac_cmd_else);
    TAC * b11 = tac_join(b1, label_end);

    return tac_join(b00, b11);
}

/**
 * LOOP (tac_exp) tac_cmd
 * 
 * @param tac_exp
 * @param tac_cmd
 * @return 
 */
TAC * make_loop(TAC * tac_exp, TAC * tac_cmd)
{
    // BASIC IDEA
    // labelStart               | B1    | B12   | RES
    // JZ labelEnd expression   |_      |       |
    //  command                 | B2    |       |
    //  JMP labelStart          |_      |       |
    // labelEnd                                 |

    // TAC creation
    TAC * label_start, * label_end, * jz_end, * jmp_start;
    label_start = tac_create(TAC_LABEL, makeLabel(), NULL, NULL);
    label_end = tac_create(TAC_LABEL, makeLabel(), NULL, NULL);
    jmp_start = tac_create(TAC_JMP, label_start->target, NULL, NULL);
    jz_end = tac_create(TAC_JZ, label_end->target, tac_exp->target, NULL);

    // Joining
    TAC * b1, * b2, * b12, * res;
    b1 = tac_join(label_start, jz_end);
    b2 = tac_join(tac_cmd, jmp_start);
    b12 = tac_join(b1, b2);
    res = tac_join(b12, label_end);
    return res;
}

/*
labelStart:
        declList
        cmdBlock
        labelEnd	
 */
TAC * makeFuncDecl(TAC * identifier, TAC * declList, TAC * cmdBlock)
{
    TAC *func, *labelStart, *labelEnd;

    labelStart = tac_create(TAC_FUNC_START, identifier->target, NULL, NULL);
    labelEnd = tac_create(TAC_FUNC_END, NULL, NULL, NULL);

    if (declList != NULL)
        func = tac_join(declList, tac_join(cmdBlock, labelEnd));
    else
        func = tac_join(cmdBlock, labelEnd);
    func = tac_join(labelStart, func);

    return func;
}

TAC * makeFuncFunCall(TAC * identifier, TAC * arguments)
{
    TAC * funcCall;

    funcCall = tac_create(TAC_FUNC_CALL, identifier->target, NULL, NULL); //TAC_FUNC_CALL goes to label identifier->target
    funcCall = tac_join(funcCall, tac_create(TAC_POP_PARAMS, NULL, NULL, NULL));
    funcCall = tac_join(funcCall, tac_create(TAC_FUNC_RET, makeTemp(), identifier ? identifier->target : NULL, NULL));
    funcCall = tac_join(arguments, funcCall);

    return funcCall;
}

TAC * makeFuncParams(ASTREE *node)
{
    TAC * argument = NULL;

    if (!node)
        return NULL;

    argument = tac_create(TAC_PUSH_PARAM, node->son[0]->symbol,
                          node->son[1] ? node->son[1]->symbol : NULL, NULL);
    argument = tac_join(argument, makeFuncParams(node->son[1]));

    return argument;
}

TAC * makeResult(TAC * retValue)
{
    return tac_create(TAC_RETURN, retValue->target, NULL, NULL);
}


/* 
 *
 */
TAC * makeArrayDecl(TAC * identifier, TAC * index, TAC * iniList) 
{
	TAC * newTac, * result;
	Entry * value, * indexEntry;
	char buffer[10];
	int i, max, val;
	
	if( iniList == NULL ) {
	
		// Make default initialization value	
		sprintf(buffer, "%d", 0);
		value = add(hashtable, buffer, LIT_INTEGER);
		
		// Get the size of the vector
		max = atoi(index->target->text);
		
		// Iterates over the vector initializing each one of the indexes
		for(i = 0; i < max; i++) {
		
			// Make an index
			sprintf(buffer, "%d", i);	
			indexEntry = add(hashtable, buffer, LIT_INTEGER);
			
			// Creates the corresponding TAC
			newTac = tac_create(TAC_VEC_INI, identifier->target, indexEntry, value);
			
			// Updates the TAC list
			if(i == 0)
				result = tac_join(newTac, NULL);
			else
				result = tac_join(result, newTac);
		}
	
		return result;
	}	
		
	else {
		//ASTREE_ARRAY_DECL_LITS
		
		// Get the size of the vector
		max = atoi(index->target->text);
		
		// Iterates over the vector initializing each one of the indexes
		for(i = 0; i < max; i++) {
		
			// Make an index
			sprintf(buffer, "%d", i);	
			indexEntry = add(hashtable, buffer, LIT_INTEGER);
						
			// Make the initialization value
			val = atoi(iniList->target->text);			
			sprintf(buffer, "%d", val);
			value = add(hashtable, buffer, LIT_INTEGER);
			iniList = iniList->prev;				
			
			// Creates the corresponding TAC
			newTac = tac_create(TAC_VEC_INI, identifier->target, indexEntry, value);
			
			// Updates the TAC list
			if(i == 0)
				result = tac_join(newTac, NULL);
			else
				result = tac_join(result, newTac);
		}
	
		return result;
	}
}


TAC * makePointerDecl(TAC * identifier, TAC * value)
{
	TAC * result;
	
	result = tac_create(TAC_POINTER_DECL, identifier->target, value->target, NULL);
	return result;
}


TAC * makeInput(TAC * identifier) 
{
	TAC * result, * input;
	
	input = tac_create(TAC_INPUT, makeTemp(), NULL, NULL);
	result = tac_create(TAC_MOV, identifier->target, input->target, NULL);
	result = tac_join(input, result);
	return result;
}


TAC * makeOutput(TAC * exp, TAC * outList)
{
	TAC * result = NULL, * output, *exp1;

	exp1 = exp;

	while(exp != NULL) {	
		output = tac_create(exp->type, exp->target, exp->op1, exp->op2);
		result = tac_join(output, result);		
		exp = exp->prev;
	}
	
	output = tac_create(TAC_OUTPUT, exp1->target, NULL, NULL);	
	result = tac_join(result, output);	
	result = tac_join(result, outList);		
		
	return result;
}

/* 
 * TAC_VECT_ASS( identifier, index, value )
 */
TAC * make_VectAss(TAC * identifier, TAC * indexExp, TAC * exp) 
{
	TAC * result, * vect;
	
	vect = tac_create(TAC_MOV_VEC, identifier->target, indexExp->target, exp->target);
	result = tac_join(indexExp, exp);
	result = tac_join(result, vect);
	
	return result;
}


TAC * make_VectAccess(TAC * identifier, TAC * exp) 
{
	TAC * result;
	
	result = tac_create(TAC_VEC_ACCESS, makeTemp(), identifier->target, exp->target);
	result = tac_join(exp, result);
	
	return result;
}


TAC *  makeRefAraay(TAC * identifier, TAC * exp)
{
	TAC * result;
	
	result = tac_create(TAC_REF_VEC, makeTemp(), identifier->target, exp->target);
	result = tac_join(exp, result);
	
	return result;
}







