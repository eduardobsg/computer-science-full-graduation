#include<stdlib.h>

#include "semantics.h"
#include "hashtable.h"
#include "y.tab.h"

// FK new stuff

int isDeclared(ASTREE * node)
{
    if (*(node->symbol->semanticType) == -1) {
        fprintf(stderr, "Error on line %i: identifier '%s' is not declared\n", node->lineNumber, node->symbol->text);
        return 0;
    }
    return 1;

}

/**
 * Verify the final type of expression recursivelly
 * @param node root
 * @return the equivalent type of the expression
 */
int typeOfExpression(ASTREE * node)
{
    /*
    #define ASTREE_ADD		
    #define ASTREE_SUB		
    #define ASTREE_MUL		
    #define ASTREE_DIV		
    #define ASTREE_OPERATOR_LE         
    #define ASTREE_OPERATOR_GE	
    #define ASTREE_OPERATOR_EQ	
    #define ASTREE_OPERATOR_NE	
    #define ASTREE_OPERATOR_OR	
    #define ASTREE_OPERATOR_AND	
    #define ASTREE_OPERATOR_GREATER
    #define ASTREE_OPERATOR_LESS
    #define ASTREE_VECT_ACCESS	
    #define ASTREE_EXP_PARENTESIS
    #define ASTREE_FUNC_CALL	
    #define ASTREE_FUNC_CALL_LIST
    #define ASTREE_UNARY_MINUS	
    #define ASTREE_POINTER_REFERENCE   
    #define ASTREE_POINTER_DEREFERENCE 
     */

    //fprintf(stderr, "semantics.typeOfExpression(%s '%s')\n", tr(node->nodeType), node->symbol == NULL ? "NULL" : node->symbol->text);
    int typeToBeReturned, arrayIndexType;
    switch (node->nodeType) {
        //
        // ARITHMETIC EXPRESSiONS: return word, arguments are word
    case ASTREE_ADD:
    case ASTREE_SUB:
    case ASTREE_MUL:
    case ASTREE_DIV:
        typeToBeReturned = typeMerge(
                                     typeOfExpression(node->son[0]),
                                     typeOfExpression(node->son[1]));
        // return type SHOULD be KW_WORD
        if (typeToBeReturned != KW_WORD) {
            // exception to the rule
            if (node->nodeType == ASTREE_ADD && (typeToBeReturned == KW_WORD_POINTER || typeToBeReturned == KW_BOOL_POINTER)) {
                return typeToBeReturned;
            }
            fprintf(stderr, "Error on line %i: the only allowed pointer arithmetic is ADD.\n", node->lineNumber);
        }
        return KW_WORD;
    case ASTREE_VECT_ACCESS:
        ; // case needs an expression here o.O
        if (!isDeclared(node->son[0])) {
            fprintf(stderr, "Error on line %i: array is not declared.\n", node->lineNumber);
        }
        // check index expression, must be word
        arrayIndexType = typeOfExpression(node->son[1]);
        if (arrayIndexType != KW_WORD && arrayIndexType != KW_BYTE) {
            fprintf(stderr, "Error on line %i: array index must be of type 'word' or 'byte'.\n", node->lineNumber);
        }
        // check if identifier is an array
        int varType = *(node->son[0]->symbol->varType);
        if (varType != VAR_ARRAY) {
            fprintf(stderr, "Error on line %i: identifier used as array was declared as %s.\n", node->lineNumber, tr(varType));
        }
        // return type is the array type
        return *(node->son[0]->symbol->semanticType);
        break;
        // identifiers and literals
    case ASTREE_SYMBOL:
        isDeclared(node);
        if (!isSymbolPutToCorrectUse(node)) break;
        // verify if symbol is put to correct use
        return *(node->symbol->semanticType);
        //
        // BOOLEAN EXPRESSIONS: return boolean, arguments are word
    case ASTREE_OPERATOR_LE:
    case ASTREE_OPERATOR_GE:
    case ASTREE_OPERATOR_EQ:
    case ASTREE_OPERATOR_NE:
    case ASTREE_OPERATOR_GREATER:
    case ASTREE_OPERATOR_LESS:
        typeToBeReturned = typeMerge(
                                     typeOfExpression(node->son[0]),
                                     typeOfExpression(node->son[1]));
        if (typeToBeReturned != KW_WORD) {
            fprintf(stderr, "Error on line %i: 'word' type arguments expected at logic expression.\n", node->lineNumber);
        }
        return KW_BOOL;
        //
        // BOOLEAN EXPRESSIONS: return boolean, arguments are boolean.
    case ASTREE_OPERATOR_OR:
    case ASTREE_OPERATOR_AND:
        typeToBeReturned = typeMerge(
                                     typeOfExpression(node->son[0]),
                                     typeOfExpression(node->son[1]));
        if (typeToBeReturned != KW_BOOL) {
            fprintf(stderr, "Error on line %i: 'bool' type arguments expected at logic expression.\n", node->lineNumber);
        }
        return KW_BOOL;
        //
        // SPECIAL EXPRESSIONS
    case ASTREE_EXP_PARENTESIS:
        return typeOfExpression(node->son[0]);
    case ASTREE_UNARY_MINUS:
        typeToBeReturned = typeOfExpression(node->son[0]);
        if (typeToBeReturned != KW_WORD) {
            fprintf(stderr, "Error on line %i: 'word' type argument expected by unary operator.\n", node->lineNumber);
        }
        return KW_WORD;
    case ASTREE_POINTER_DEREFERENCE:
        isDeclared(node->son[0]);
        typeToBeReturned = typeOfExpression(node->son[0]);
        if (typeToBeReturned == KW_WORD_POINTER) {
            return KW_WORD;
        }
        else if (typeToBeReturned == KW_BOOL_POINTER) {
            return KW_BOOL;
        }
        fprintf(stderr, "Error on line %i: a pointer dereference needs a pointer to operate on [%s] .\n", node->lineNumber, tr(typeToBeReturned));
        // dereferencing something that is not a pointer will always produce garbage (word)
        return KW_WORD;
    case ASTREE_POINTER_REFERENCE:
        isDeclared(node->son[0]);
        // must be a VAR_SIMPLE identifier
        if (*(node->son[0]->symbol->varType) != VAR_SIMPLE) {
            fprintf(stderr, "Error on line %i: reference expects a simple variable.\n", node->lineNumber);
            // in this case, choose a type to return...
            return -1;
        }
        // returning type is type of array
        typeToBeReturned = *(node->son[0]->symbol->semanticType);
        if (typeToBeReturned == KW_WORD) {
            return KW_WORD_POINTER;
        }
        else if (typeToBeReturned == KW_BOOL) {
            return KW_BOOL_POINTER;
        }
        else {
            fprintf(stderr, "Error on line %i: reference expects 'word' or 'bool', got %s instead.\n", node->lineNumber, tr(typeToBeReturned));
        }
        break;
    case ASTREE_POINTER_REFERENCE_ARRAY:
        isDeclared(node->son[0]);
        // must be a VAR_ARRAY identifier
        if (*(node->son[0]->symbol->varType) != VAR_ARRAY) {
            fprintf(stderr, "Error on line %i: reference expects a array identifier.\n", node->lineNumber);
            return -1;
        }
        // type of expression at the index
        arrayIndexType = typeOfExpression(node->son[1]);
        if (arrayIndexType != KW_WORD && arrayIndexType != KW_BYTE) {
            fprintf(stderr, "Error on line %i: array index must be 'word' or 'byte'.\n", node->lineNumber);
        }
        // returning type is type of array
        typeToBeReturned = *(node->son[0]->symbol->semanticType);
        if (typeToBeReturned == KW_WORD) {
            return KW_WORD_POINTER;
        }
        else if (typeToBeReturned == KW_BOOL) {
            return KW_BOOL_POINTER;
        }
        else {
            fprintf(stderr, "Error on line %i: array reference expects 'word' or 'bool', got %s instead.\n", node->lineNumber, tr(typeToBeReturned));
        }
        break;
        //
    case ASTREE_FUNC_CALL:// nem sabia que podia ter isso nas expressões
        ; // case needs an expression here o.O
        if (!isDeclared(node->son[0])) {
            fprintf(stderr, "Error on line %i: function is not declared.\n", node->lineNumber);
        }
        // check if identifier is a functiob
        if (!isSymbolPutToCorrectUse(node)) {
            break;
        }
        // return type is the array type
        return *(node->son[0]->symbol->semanticType);
        //
        // ERR
    default:
        fprintf(stderr, "ERR semantics.typeOfExpression(%s)\n", tr(node->nodeType));
    }
    return -1;
}


/*

*/
int isSymbolPutToCorrectUse(ASTREE * node)
{
    int typeFound;
    switch (node->nodeType) {
    case ASTREE_FUNC_CALL:
        typeFound = *(node->son[0]->symbol->varType);
        if (typeFound == FUNCTION)
            return 1;
        fprintf(stderr, "Error on line %i: identifier used as function was declared as %s.\n", node->lineNumber, tr(typeFound));
        break;
    case ASTREE_SYMBOL:
        typeFound = *(node->symbol->varType);
        if (typeFound == VAR_SIMPLE || typeFound == VAR_POINTER || typeFound == -1) // -1 is for literals, that remain unset
            return 1;
        fprintf(stderr, "Error on line %i: identifier used as variable was declared as %s.\n", node->lineNumber, tr(typeFound));
        break;
    default:
        fprintf(stderr, "Semantics::isSymbolPutToCorrectUse() wrong symbol to analyze.\n");
        return 0;
    }
    return 0;
}

/**
 * When a expression has 2 sides, there are no guaranties
 * that they will be the same. In some cases thats not
 * an error, as we can sum a pointer and a word like
 * pt = pt + 1 (resulting type on the right IS pointer)
 *
 * @param node root
 * @return the predominant type of the expression
 */
int typeMerge(int typeA, int typeB)
{
    //fprintf(stderr, "semantics.typeMerge(%s, %s)\n", tr(typeA), tr(typeB));
    // TRIVIAL: same types
    if ((typeA == KW_WORD && typeB == KW_WORD) ||
        (typeA == KW_BYTE && typeB == KW_BYTE) ||
        (typeA == KW_BOOL && typeB == KW_BOOL)) {
        return typeA;
    }
    // WORD and BYTE do merge
    if ((typeA == KW_WORD && typeB == KW_BYTE) ||
        (typeA == KW_BYTE && typeB == KW_WORD)) {
        return KW_WORD;
    }
    // ALLOWING POINTERS
    if (typeA == KW_BOOL_POINTER ||
        typeA == KW_WORD_POINTER) {
        // the only type that don't mix with pointers
        if (typeA == KW_BOOL || typeB == KW_BOOL || typeB != KW_WORD) {
            //fprintf(stderr, "ERR semantics.typeMerge() type 0\n");
            return -1;
        }
        // Otherwise it must be a pointer and a (word or byte)
        return typeA;
    }
    if (typeB == KW_BOOL_POINTER ||
        typeB == KW_WORD_POINTER) {
        // the only type that don't mix with pointers
        if (typeA == KW_BOOL || typeA == KW_BOOL || typeA != KW_WORD) {
            //fprintf(stderr, "ERR semantics.typeMerge() type 2\n");
            return -1;
        }
        // Otherwise it must be a (word or byte) and a pointer
        return typeB;
    }
    //fprintf(stderr, "ERR semantics.typeMerge() type mismatch [%s|%s]\n", tr(typeA), tr(typeB));
    return -1;
}

/**
 * Verify if assigned type match
 * 
 * @param node ASTREE_SCALA_ASS
 */
void check_ASTREE_SCALA_ASS(ASTREE * node)
{
    int leftHandType, rightHandType;

    leftHandType = *(node->son[0]->symbol->semanticType);
    rightHandType = typeOfExpression(node->son[1]);
    if (leftHandType == rightHandType ||
        (leftHandType == KW_WORD && rightHandType == KW_BYTE) || // because they mix..
        (leftHandType == KW_BYTE && rightHandType == KW_WORD)) {
        // do nothing
        // too tired to do Morgan's law 
    }
    else {
        fprintf(stderr, "Error on line %i: type mismatch in assignment '%s = %s'\n", node->lineNumber, tr(leftHandType), tr(rightHandType));
    }
}

/**
 * Translates constants back into strings ;)
 * 
 * @param value
 * @return value String
 */
char * tr(int value)
{
    switch (value) {
    case -1:
        return "UNSET";
        // SEMANTIC TYPES
    case KW_WORD: return "word";
    case KW_BYTE: return "byte";
    case KW_BOOL: return "bool";
    case KW_WORD_POINTER: return "word_pointer";
    case KW_BOOL_POINTER: return "bool_pointer";
        // LEXICAL TYPES
    case LIT_INTEGER: return "LIT_INTEGER";
    case LIT_FALSE: return "LIT_FALSE";
    case LIT_TRUE: return "LIT_TRUE";
    case LIT_CHAR: return "LIT_CHAR";
        // other nodes
    case ASTREE_PROGRAM: return "PROGRAM";
    case ASTREE_SYMBOL: return "SYMBOL";
        // EXPRESSIONS - generic
    case ASTREE_UNARY_MINUS: return "UNARY_MINUS";
    case ASTREE_POINTER_REFERENCE: return "POINTER_REFERENCE";
    case ASTREE_POINTER_DEREFERENCE: return "POINTER_DEREFERENCE";
    case ASTREE_POINTER_REFERENCE_ARRAY: return "ASTREE_POINTER_REFERENCE_ARRAY";
    case ASTREE_EXP_PARENTESIS: return "EXP_PARENTESIS";
        // EXPRESSIONS - arithmetic
    case ASTREE_ADD: return "ADD";
    case ASTREE_SUB: return "SUB";
    case ASTREE_MUL: return "MUL";
    case ASTREE_DIV: return "DIV";
        // EXPRESSIONS - logic
    case ASTREE_OPERATOR_GE: return "OPERATOR_GE";
    case ASTREE_OPERATOR_LE: return "OPERATOR_LE";
    case ASTREE_OPERATOR_EQ: return "OPERATOR_EQ";
    case ASTREE_OPERATOR_NE: return "OPERATOR_NE";
    case ASTREE_OPERATOR_AND: return "OPERATOR_AND";
    case ASTREE_OPERATOR_OR: return "OPERATOR_OR";
    case ASTREE_OPERATOR_GREATER: return "OPERATOR_GREATER";
    case ASTREE_OPERATOR_LESS: return "OPERATOR_LESS";
        // other stuff
    case ASTREE_SCALA_ASS: return "SCALA_ASS";
    case ASTREE_VECT_SCALA_ASS: return "VECT_SCALAR_ASSIGNMENT";
    case ASTREE_CMDL: return "CMDL";
    case ASTREE_CMD_BLOCK: return "CMD_BLOCK";
    case ASTREE_SIMPLE_DECL: return "SIMPLE_DECL";
    case ASTREE_ARRAY_DECL: return "ARRAY_DECL";
    case ASTREE_ARRAY_DECL_INI: return "ARRAY_DECL_INICIALIZATION";
    case ASTREE_ARRAY_DECL_LITS: return "ARRAY_DECL_INI_LITERALS";
    case ASTREE_POINTER_DECL: return "POINTER_DECL";
    case ASTREE_DECL: return "DECL";
    case ASTREE_FUNC: return "FUNC";
    case ASTREE_FUNC1: return "FUNC1";
    case ASTREE_FUNC2: return "FUNC2";
    case ASTREE_FUNC3: return "FUNC3";
    case ASTREE_FUNC4: return "FUNC4";
    case ASTREE_FUNC_PARAM: return "FUNC_PARAM";
    case ASTREE_FUNC_DECL: return "FUNC_DECL";
    case ASTREE_IF: return "IF";
    case ASTREE_IF_ELSE: return "IF_ELSE";
    case ASTREE_VECT_ACCESS: return "VECT_ACCESS";
    case ASTREE_FUNC_CALL: return "FUNC_CALL";
    case ASTREE_FUNC_CALL_LIST: return "FUNC_CALL_LIST";
    case ASTREE_LOOP: return "LOOP";
    case ASTREE_INPUT: return "INPUT";
    case ASTREE_RETURN: return "RETURN";
    case ASTREE_OUTPUT: return "OUTPUT";
    case ASTREE_OUTPUT_LIST: return "OUTPUT_LIST";
        // VAR TYPES (from hashtable.h)
    case FUNCTION: return "FUNCTION";
    case VAR_ARRAY: return "VAR_ARRAY";
    case VAR_POINTER: return "VAR_POINTER";
    case VAR_SIMPLE: return "VAR_SIMPLE";
    default:
        fprintf(stderr, "ERR semantics.tr(%i) UNKNOWN\n", value);
        return "???";
    }
}

/**
 * Given a node of the syntax tree and a semanticType, the function
 * updates the hashtable node of this syntax trre node with the a
 * semanticType. 
 *
 * If the semanticType is already updated, i. e, different from -1,
 * then the symbol in the hashtable associated with the syntax tree 
 * node, is already defined.
 * 
 * @param node
 * @param semanticType
 * @return a pointer to the node of the hash
 */
void updateAndCheckNode(ASTREE *node, int semanticType, int varType, int lineNumber)
{
    Entry *n = node->symbol;

    /* Checks for double definition */
    if (*(n->varType) != -1) { //symbol already defined
    
    	if( lineNumber == -1 )
	        fprintf(stderr, "Error on line %i: '%s' is already defined.\n", getLineNumber(), n->text);
	    else
	    	fprintf(stderr, "Error on line %i: '%s' is already defined.\n", lineNumber, n->text);
    }
    else {
        *(n->varType) = varType;

        if (varType == VAR_POINTER) {
            switch (semanticType) {
            case KW_WORD:
                *(n->semanticType) = KW_WORD_POINTER;
                break;
            case KW_BOOL:
                *(n->semanticType) = KW_BOOL_POINTER;
                break;
            default:
                fprintf(stderr, "ERR semantics.updateAndCheckNode() wrong pointer type\n");
                *(n->semanticType) = -1;
            }
        }
        else {
            *(n->semanticType) = semanticType;
        }

        node->symbol = n;
    }

}

/**
 * When a function is declared its parameters anexed to the 
 * hash node. This functions counts the number of parameters
 * and saves the types of the variables, in order of appearance,
 * in the 'parameters' variable of the hash node.
 *
 * contentType: word, byte or bool
 *
 * @param node
 * @param paramList
 * @return a pointer to the node of the astree
 */
ASTREE * fillParamList(ASTREE *node, ASTREE *paramList)
{
    Entry *n = node->symbol;
    ASTREE *a = paramList;
    int quant = 4;

    if (paramList == NULL) {
        *(n->quant) = 0;
    }
    else {
        for (quant = 1; a->son[1] != NULL; quant++, a = a->son[1]);
        *(n->quant) = quant;
        n->parameters = malloc(quant * sizeof (int));

        a = paramList;
        for (quant = 0; a->son[1] != NULL; quant++, a = a->son[1]) {

            n->parameters[quant] = a->contentType;
        }

        n->parameters[quant] = a->contentType;
        node->symbol = n;
    }

    return node;
}

/**
 * When a function call is used, this function checks if the number
 * of arguments of the function call is correct and if the types
 * of variables or expressions also are.
 *
 * @param node
 * @param funcArgs
 * @return a pointer to the node of the astree
 */
ASTREE * checkFunctionParameters(ASTREE *node, ASTREE *funcArgs)
{
    Entry *n = node->symbol;
    int expectedNumberOfParams = *(n->quant);

    if (expectedNumberOfParams == -1)
        return node; // ignore, because we are not looking at a function

    // Tests the quantity and types of parameters of the function call
    if (funcArgs == NULL) {
        if (expectedNumberOfParams == 0)
            return node;
        else {
            fprintf(stderr, "Error on line %d: Wrong parameter number\n", node->lineNumber);
            return node;
        }
    }
    else {
        int iterator, typeParamOnHash, contentType;
        ASTREE *parameter = funcArgs;

        // Check the number of parameters
        for (iterator = 1;
                parameter->son[1] != NULL;
                iterator++, parameter = parameter->son[1]);

        if (iterator != expectedNumberOfParams) {
            fprintf(stderr, "Error on line %d: Wrong number of parameters, must have %d parameters.\n",
                    node->lineNumber, expectedNumberOfParams);
            return node;
        }

        for (iterator = 0;
                iterator < expectedNumberOfParams;
                iterator++, funcArgs = funcArgs->son[1]) {

            parameter = funcArgs->son[0];

            // Gets the type of the 'iterator' parameter of the list of parameter types in the hash
            typeParamOnHash = n->parameters[iterator];
            contentType = typeOfExpression(parameter);

            //fprintf(stderr, "typeParamOnHash[%d]: %d, contentType: %d\n", iterator, n->parameters[iterator], checkParameter(parameter));

            if ((typeParamOnHash == KW_WORD && contentType == KW_BYTE) ||
                (typeParamOnHash == KW_WORD && contentType == KW_WORD) ||
                (typeParamOnHash == KW_BYTE && contentType == KW_BYTE) ||
                (typeParamOnHash == KW_BYTE && contentType == KW_WORD) ||
                (typeParamOnHash == KW_BOOL && contentType == KW_BOOL)
                )
                continue;
            else {
                fprintf(stderr, "Error on line %d: ", node->lineNumber);
                fprintf(stderr, "parameter %d with wrong type, must be of type ", iterator + 1);
                switch (typeParamOnHash) {

                case KW_WORD:
                case KW_BYTE:
                    fprintf(stderr, "word or byte\n");
                    break;
                case KW_BOOL:
                    fprintf(stderr, "bool\n");
                    break;
                }
                return node;
            }
        }

        return node;
    }
}

/**
 * Match semanticType type against a lexicalType type.
 * 
 * @param expecsemanticTypeted as KW_WORD, KW_BOOL, KW_BYTE
 * @param lexicalType as LIT_INTEGER, LIT_TRUE, LIT_FALSE, LIT_CHAR
 * @return 1 if types match, 0 otherwise.
 */
int checkTypeMatch(int semanticType, int lexicalType)
{
    switch (semanticType) {

    case KW_WORD:
    case KW_BYTE:// interchangeable
        return (lexicalType == LIT_INTEGER || lexicalType == LIT_CHAR) ? 1 : 0;
    case KW_BOOL:
        return (lexicalType == LIT_TRUE || lexicalType == LIT_FALSE) ? 1 : 0;
    default:
        return -1;
    }
}

/**
 * Given the ASTREE top node, make recursive calls checking
 * all the tree.
 *
 * @param node
 */
void astreeSemanticCheck(ASTREE *node)
{
    if (!node) {
        return;
    }

    int identifierType, argumentType;

    switch (node->nodeType) {

    case ASTREE_SIMPLE_DECL:
       
    	updateAndCheckNode(node->son[0], node->contentType, VAR_SIMPLE, node->lineNumber);
        identifierType = *(node->son[0]->symbol->semanticType); // KW_WORD, KW_BOOL, KW_BYTE
        argumentType = *(node->son[1]->symbol->lexicalType); // LIT_TRUE, LIT_FALSE, ... etc

        if (!checkTypeMatch(identifierType, argumentType)) {
            fprintf(stderr, "Error on line %i: var '%s' expects type %s\n", node->lineNumber,
                    node->son[0]->symbol->text, tr(*(node->son[0]->symbol->semanticType)));
        }
        break;

    case ASTREE_POINTER_DECL:
    
    	updateAndCheckNode(node->son[0], node->contentType, VAR_POINTER, node->lineNumber);
        identifierType = *(node->son[0]->symbol->semanticType);
        argumentType = *(node->son[1]->symbol->lexicalType);

        if (!checkTypeMatch(identifierType, argumentType)) {
            fprintf(stderr, "Error on line %i: pointer '%s' expects type %s\n", node->lineNumber,
                    node->son[0]->symbol->text, tr(*(node->son[0]->symbol->semanticType)));
        }
        break;

    case ASTREE_ARRAY_DECL_INI:
        ; // expression expected! - must keep

        ASTREE * currentLiteral; // pointer for the first of the list
        int numberOfElements = atoi(node->son[1]->symbol->text); // size of array
        int i;

		updateAndCheckNode(node->son[0], node->contentType, VAR_ARRAY, node->lineNumber); 

        // Verify number of args
        currentLiteral = node->son[2];
        for (i = 0; currentLiteral != NULL; i++, currentLiteral = currentLiteral->son[1]);
        if (i != numberOfElements) {
            fprintf(stderr, "Error on line %i: array expected %i arguments, had %i\n",
                    node->lineNumber, numberOfElements, i);
            break;
        }

        // Verify each ASTREE_ARRAY_DECL_INI for its type
        identifierType = *(node->son[0]->symbol->semanticType);
        currentLiteral = node->son[2];
        for (i = 0; currentLiteral != NULL; i++, currentLiteral = currentLiteral->son[1]) {
            argumentType = *(currentLiteral->son[0]->symbol->lexicalType);

            if (!checkTypeMatch(identifierType, argumentType)) {
                fprintf(stderr, "Error on line %i: ", node->lineNumber);
                fprintf(stderr, "array expects type %s. Param %i had type %s\n",
                        tr(*(node->son[0]->symbol->semanticType)), i + 1, tr(*(currentLiteral->son[0]->symbol->semanticType)));
                break;
            }
        }
        break;

	case ASTREE_ARRAY_DECL:
		updateAndCheckNode(node->son[0], node->contentType, VAR_ARRAY, node->lineNumber);
		break;

    case ASTREE_FUNC_CALL:
        node = checkFunctionParameters(node->son[0], node->son[1]);
        break;

    case ASTREE_FUNC:
        verifyFunctionReturnType(node);
        break;

    case ASTREE_INPUT:
        testIfDeclaredAndCorrectUse(node->son[0], VAR_SIMPLE);
        break;

    case ASTREE_SCALA_ASS:
    	if( *(node->son[0]->symbol->varType) != VAR_POINTER)
	        testIfDeclaredAndCorrectUse(node->son[0], VAR_SIMPLE);
	        
        if (isDeclared(node->son[0])) {
            check_ASTREE_SCALA_ASS(node);
        }
        break;

    case ASTREE_VECT_SCALA_ASS:
        testIfDeclaredAndCorrectUse(node->son[0], VAR_ARRAY);
        testIndexType(node->son[1]);
        break;

        //case ASTREE_POINTER_DEREFERENCE:
        //    testIfDeclaredAndCorrectUse(node->son[0], VAR_POINTER);
        //    break;

    case ASTREE_POINTER_REFERENCE:
        testIfDeclaredAndCorrectUse(node->son[0], VAR_POINTER);
        break;
    }

    // Analyze Everything
    astreeSemanticCheck(node->son[0]);
    astreeSemanticCheck(node->son[1]);
    astreeSemanticCheck(node->son[2]);
    astreeSemanticCheck(node->son[3]);
}

/**
 * Check the type of the index. Must be word or byte.
 *
 * @param node
 */
void testIndexType(ASTREE *node)
{
    int contentType;

    contentType = typeOfExpression(node);

    if (contentType == KW_WORD || contentType == KW_BYTE) {
        return;
    }
    else {

        fprintf(stderr, "Error on line %d: ", node->lineNumber);
        fprintf(stderr, "vector index not a word or byte\n");
        return;
    }
}

/**
 * Check if identifier is declared and being correctly used.
 *
 * @param node
 * @param varType
 */
void testIfDeclaredAndCorrectUse(ASTREE *node, int varType)
{
    Entry *n = node->symbol;

    // Check if identifier is declared
    if (*(n->semanticType) == -1) {
        fprintf(stderr, "Error on line %d: ", node->lineNumber);
        fprintf(stderr, "identifier '%s' is not declared and should not be used\n", n->text);
        return;
    }

    //Just want to check if it's declared
    if (varType == -1)
        return;

    // Check is identifier is being used correctly
    n = node->symbol;
    if (*(n->varType) != varType && varType != VAR_POINTER) {//VAR_POINTER is taken care of in typeOfExpression()
        // identifier used as variable was declared as
        fprintf(stderr, "Error on line %i: identifier used as %s was declared as %s\n",
                node->lineNumber, tr(varType), tr(*(n->varType)));
        return;
    }

    return;
}

/**
 * Check if the return type of a function matches 
 * with the function semanticType.
 */
void verifyFunctionReturnType(ASTREE * node)
{
    //Type of function: FUNC1, FUNC2, FUNC3 or FUNC4
    ASTREE * funcn = node->son[0];

    // function name: SYMBOL
    ASTREE * fname = funcn->son[0];

    // expected type
    int semanticFuncType;
    semanticFuncType = *(fname->symbol->semanticType);

    // Find the command block
    ASTREE * cmdBlock;

    switch (funcn->nodeType) {
    case ASTREE_FUNC1:
        cmdBlock = funcn->son[3];
        break;
    case ASTREE_FUNC2:
    case ASTREE_FUNC3:
        cmdBlock = funcn->son[2];
        break;
    case ASTREE_FUNC4:
        cmdBlock = funcn->son[1];
        break;
    default:
        printf("Error in function 'verifyFunctionReturnType'\n");
        exit(1);
        break;
    }

    // receivedType type, and verification
    int receivedType = 0, returnCommandLine = 0;
    getSemanticTypeOfCommandBlock(cmdBlock, &receivedType, &returnCommandLine);

    if (receivedType == 0) {
        fprintf(stderr, "Error on line %d: return command of function '%s' with invalid type. Should be %s\n",
                returnCommandLine, fname->symbol->text, tr(*(node->son[0]->son[0]->symbol->semanticType)));
    }
    else if (receivedType == -1) {
        fprintf(stderr, "Error on line %d: function body must have a return command\n",
                node->son[0]->son[0]->lineNumber);
    }
    else if (semanticFuncType != receivedType) {

        fprintf(stderr, "Error on line %d: function body has wrong return type. Should be %s\n",
                returnCommandLine, tr(*(node->son[0]->son[0]->symbol->semanticType)));
    }
}

/**
 * Given a functions command block, the semanticType 
 * of the return command is returned.
 */
void getSemanticTypeOfCommandBlock(ASTREE *node, int *receivedType, int *returnCommandLine)
{
    // Root of command list
    ASTREE * cmdList;
    cmdList = node->son[0];

    // Find last
    while (cmdList != NULL) {
        if (cmdList->son[1] == NULL || cmdList->son[1]->nodeType != ASTREE_CMDL) {
            break;
        }
        cmdList = cmdList->son[1];
    }

    if (cmdList->son[0]->nodeType == ASTREE_RETURN) {
        *returnCommandLine = cmdList->son[0]->lineNumber;
        *receivedType = typeOfExpression(cmdList->son[0]->son[0]);
        if (*receivedType == -1)
            *receivedType = 0;
        return;
    }

    *receivedType = -1;
    return;
}
