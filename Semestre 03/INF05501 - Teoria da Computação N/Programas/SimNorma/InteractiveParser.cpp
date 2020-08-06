/********************************************************************
	IMPLEMENTAÇÃO DA CLASSE ITERACTIVEPARSER
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "Parser.h"
#include "ParserData.h"


/********************************************************************
	CLASSE ITERACTIVEPARSER */

bool ITERACTIVEPARSER::Parse (bool bIsMacro, bool bRemoveNullOp)
{
	// Parse - inicia o parsing de um programa iterativo
	prog = pSourceProg;
	err_pos = NULL;

	// atualiza os flags internos
	support_exit = bIsMacro;
	support_null = !bRemoveNullOp;

	// pega o primeiro token
	get_token ();
	if (tok_type == ittEnd)
	{
		err_type = ietEnd;
		err_pos = prog - 1;
		return false;
	}

	// avalia o programa
	LABEL *pResult = NULL;
	if (!evaluate_instruction (pResult, NULL, NULL, NULL))
	{
		err_pos = prog - 1;
		return false;
	}

	// verifica se chegou realmente ao fim
	if ((bIsMacro && (tok_type == ittEndMacro)) ||
		(!bIsMacro && (tok_type == ittEnd)))
		return true;
	else
	{
		if (bIsMacro)
			err_type = ietEndMacroExpected;
		else
			err_type = ietEndExpected;
		err_pos = prog - 1;
		return false;
	}
}

void ITERACTIVEPARSER::get_token ()
{
	// get_token - pega e identifica o proximo token
	char *tok;
	I_TOK_TYPE last_tok_type;

	// ignora espaços, tabs, enters
	while ((*prog == ' ') || (*prog == '\t') || (*prog == 13) || (*prog == 10) || (*prog == -51) || (*prog == '{'))
	{
		if (*prog == '{')
		{
			// pula os comentários
			prog++;
			while (*prog && (*prog != '}'))
				prog++;
			if (*prog == '}')
				prog++;
		}
		else
			prog++;
	}

	// verifica se chegou ao fim
	if (!*prog)
	{
		tok_type = ittEnd;
		return;
	}

	// guarda o token atual para comparações posteriores
	tok = token;
	last_tok_type = tok_type;

	// salva o caracter atual
	*tok = *prog++;

	// verifica se o caracter era um delimitador
	if ((*tok == '(') || (*tok == ')') || (*tok == ';') || (*tok == ','))
	{
		// verifica se o delimitador esta em um condição de erro
        switch (last_tok_type)
		{
		case ittIf:
		case ittWhile:
		case ittUntil:
			{
				tok_type = ittError;
				return;
			}
		}

		// como não ocorreu erro, o delimitador é possível
		*++tok = 0;
		tok_type = ittDelimiter;
		return;
	}

	// pega o token inteiro para identificar o que ela é
	while (*prog && (*prog != ' ') && (*prog != ';') && (*prog != ',') && (*prog != '(') && (*prog != ')') && (*prog != '\t') && (*prog != 13) && (*prog != 10) && (*prog != -51) && (*prog != '{'))
		*++tok = *prog++;
	// salva o caracter nulo
	*++tok = 0;

	// identifica o token
	if (stricmp (token, DEFENDMACRO) == 0)
		tok_type = ittEndMacro;
	else if (stricmp (token, IF) == 0)
		tok_type = ittIf;
	else if (stricmp (token, THEN) == 0)
		tok_type = ittThen;
	else if (stricmp (token, ELSE) == 0)
		tok_type = ittElse;
	else if (stricmp (token, WHILE) == 0)
		tok_type = ittWhile;
	else if (stricmp (token, UNTIL) == 0)
		tok_type = ittUntil;
	else if (stricmp (token, DO) == 0)
		tok_type = ittDo;
	else if (stricmp (token, DEFEXITMACRO) == 0)
	{
		if (support_exit)
			tok_type = ittExit;
		else
			tok_type = ittError;
	}
	else
		tok_type = ittFunction;
}

bool ITERACTIVEPARSER::evaluate_instruction (LABEL *&pResult, LABEL *pPrevious, LABEL *pEndJump, STACK *pEndLabels, bool bCodeBlock)
{
	// evaluate_instruction - avalia uma instrução
	STACK *pInternalEndLabels = NULL;

	// verifica se é um erro
	if (tok_type == ittError)
	{
		err_type = ietSyntax;
		return false;
	}

	// verifica se o item atual é um parenteses
	if ((tok_type == ittDelimiter) && (token[0] == '('))
	{
		// pega o próximo token
		get_token ();
		// cria uma nova pilha
		pInternalEndLabels = new STACK ();
		// avalia a instrução
		if (!evaluate_instruction (pResult, pPrevious, pEndJump, pInternalEndLabels))
		{
			delete pInternalEndLabels;
			return false;
		}
		// verifica se o o token atual é um fecha parênteses
		if ((tok_type != ittDelimiter) || (token[0] != ')'))
		{
			err_type = ietParenthesisExpected;
			delete pInternalEndLabels;
			return false;
		}
		// pega o próximo token
		get_token ();
	}
	else if (tok_type == ittIf)
	{
		// pega o próximo token
		get_token ();
		// cria uma nova pilha
		pInternalEndLabels = new STACK ();
		// avalia a condição
		if (!(pResult = evaluate_condition (pEndJump, pInternalEndLabels)))
		{
			delete pInternalEndLabels;
			return false;
		}
	}
	else if (tok_type == ittWhile)
	{
		// pega o próximo token
		get_token ();
		// avalia o enquanto
		if (!(pResult = evaluate_while (pEndJump, pEndLabels)))
			return false;
	}
	else if (tok_type == ittUntil)
	{
		// pega o próximo token
		get_token ();
		// avalia o até
		if (!(pResult = evaluate_until (pEndJump, pEndLabels)))
			return false;
	}
	else if (tok_type == ittExit)
	{
		// sai da macro, ignorando o resto do código
		pResult = pMacroReturn;
		get_token ();
		/*// insere o rótulo anterior na pilha de atualização
		if (pPrevious)
		{
			if (pEndLabels && ((pPrevious->lType == ltOperation) || (pPrevious->lType == ltMacroOperation)))
				pEndLabels->Push (pPrevious);
		}*/
		return true;
	}
	else if (tok_type == ittFunction)
	{
		// verifica se a intrução não é vazia
		if (support_null || stricmp (token, N_NULL))
		{
			// aloca espaço para o rótulo criado e adiciona na lista
			if (!(pResult = pProgram->AddLabel ()))
			{
				err_type = ietMemory;
				return false;
			}
			// atualiza as propriedades
			pResult->lType = ltOperation;
			pResult->nIdx = pProgram->Count () - 1;
			pResult->pTrue = pEndJump;
			pResult->pFalse = pEndJump;
			// verifica se é uma operação nula
			if (stricmp (token, N_NULL))
				pResult->SetData (token);
			else
				pResult->sData = NULL;
			// pega o próximo token
			get_token ();
			// verifica se é uma chamada de macro
			if ((tok_type == ittDelimiter) && (token[0] == '('))
			{
				// pega o próximo token
				get_token ();
				// é uma chamada de macro
				pResult->lType = ltMacroOperation;
				if (!evaluate_params (pResult->pParams, pResult->nParamsCount))
					return false;
			}
		}
		else
		{
			// ignora e passa para o próximo token
			get_token ();
		}
	}
	else if ((tok_type != ittDelimiter) || (token[0] != ')'))
	{
		err_type = ietSyntax;
		return false;
	}

	// verifica se a instrução atual é composta
	if ((!bCodeBlock) && (tok_type == ittDelimiter) && (token[0] == ';'))
	{
		// pega o próximo token
		get_token ();
		// pega o rótulo anterior
		LABEL *pTmpPrevious, *pNext;
		if (pResult)
			pTmpPrevious = pResult;
		else
			pTmpPrevious = pPrevious;
		// avalia a instrução que é composta
		if (!evaluate_instruction (pNext, pTmpPrevious, pEndJump, pEndLabels))
		{
			if (pInternalEndLabels)
				delete pInternalEndLabels;
			return false;
		}
		// atualiza os ponteiros finais de pulo
		if (pInternalEndLabels)
		{
			LABEL *pEndLabel;
			while (pEndLabel = (LABEL*) pInternalEndLabels->Pop ())
				pEndLabel->SetLastJump (pNext, pEndJump);
			delete pInternalEndLabels;
		}
		// atualiza os ponteiros do resultado
		if (pResult)
			pResult->SetLastJump (pNext, pEndJump);
		else
			pResult = pNext;
	}
	// é um rótulo final, verifica se a instrução tem para onde voltar
	else
	{
		// atualiza os ponteiros finais de pulo
		if (pInternalEndLabels)
		{
			LABEL *pEndLabel;
			while (pEndLabel = (LABEL*) pInternalEndLabels->Pop ())
			{
				pEndLabel->SetLastJump (pEndJump, pEndJump);
				if (pEndLabels)
					pEndLabels->Push (pEndLabel);
			}
			delete pInternalEndLabels;
		}
		// pega o rótulo que deve ser incluído na pilha de atualizações
		LABEL *pUpdate = NULL;
		if (!pResult)
		{
			pUpdate = pPrevious;
			//pResult = pEndJump;
		}
		else
		{
			pUpdate = pResult;
			pResult->SetLastJump (pEndJump, pEndJump);
		}
		// atualiza a pilha de atualizações
		if (pUpdate)
		{
			if (pEndLabels && ((pUpdate->lType == ltOperation) || (pUpdate->lType == ltMacroOperation)))
				pEndLabels->Push (pUpdate);
		}
	}

	// returna o primeiro rótulo criado
	return true;
}

LABEL *ITERACTIVEPARSER::evaluate_condition (LABEL *pEndJump, STACK *pEndLabels)
{
	// evaluate_condition - avalia uma condição
	LABEL *pResult;

	// verifica se é um erro
	if (tok_type == ittError)
	{
		err_type = ietSyntax;
		return NULL;
	}

	// verifica se o item atual é uma função (teste)
	if (tok_type == ittFunction)
	{
		// aloca espaço para o rótulo criado
		if (!(pResult = pProgram->AddLabel ()))
		{
			err_type = ietMemory;
			return NULL;
		}

		// adiciona na lista e atualiza propriedades
		pResult->lType = ltTest;
		pResult->nIdx = pProgram->Count () - 1;

		// salva o nome da função
		pResult->SetData (token);
		// pega o próximo token
		get_token ();

		// verifica se é uma chamada de macro
		if ((tok_type == ittDelimiter) && (token[0] == '('))
		{
			// pega o próximo token
			get_token ();
			// é uma chamada de macro
			pResult->lType = ltMacroTest;
			if (!evaluate_params (pResult->pParams, pResult->nParamsCount))
				return NULL;
		}

		// verifica se é um então
		if (tok_type != ittThen)
		{
			err_type = ietThenExpected;
			return NULL;
		}
		// neste caso é um então, então pega o próximo token
		get_token ();

		// avalia a instrução
		if (!evaluate_instruction (pResult->pTrue, pResult, pEndJump, pEndLabels))
			return NULL;

		// verifica se é um senão
		if (tok_type != ittElse)
		{
			err_type = ietElseExpected;
			return NULL;
		}
		// neste caso é um senão, então pega o próximo token
		get_token ();

		// avalia a instrução
		if (!evaluate_instruction (pResult->pFalse, pResult, pEndJump, pEndLabels))
			return NULL;

		return pResult;
	}
	else
	{
		err_type = ietSyntax;
		return NULL;
	}
}

LABEL *ITERACTIVEPARSER::evaluate_while (LABEL *pEndJump, STACK *pEndLabels)
{
	// evaluate_while - avalia o enquanto
	LABEL *pResult;

	// verifica se é um erro
	if (tok_type == ittError)
	{
		err_type = ietSyntax;
		return NULL;
	}

	// verifica se o item atual é uma função (teste)
	if (tok_type == ittFunction)
	{
		// aloca espaço para o rótulo criado
		if (!(pResult = pProgram->AddLabel ()))
		{
			err_type = ietMemory;
			return NULL;
		}

		// adiciona na lista e atualiza propriedades
		pResult->lType = ltTest;
		pResult->nIdx = pProgram->Count () - 1;
		pResult->pFalse = pEndJump;

		// salva o nome da função
		pResult->SetData (token);
		// pega o próximo token
		get_token ();

		// verifica se é uma chamada de macro
		if ((tok_type == ittDelimiter) && (token[0] == '('))
		{
			// pega o próximo token
			get_token ();
			// é uma chamada de macro
			pResult->lType = ltMacroTest;
			if (!evaluate_params (pResult->pParams, pResult->nParamsCount))
				return NULL;
		}

		// verifica se é um faça
		if (tok_type != ittDo)
		{
			err_type = ietDoExpected;
			return NULL;
		}
		// neste caso é um faça, então pega o próximo token
		get_token ();

		// avalia a instrução
		if (!evaluate_instruction (pResult->pTrue, pResult, pResult, NULL, true))
			return NULL;

		// adiciona o enquanto na pilha
		if (pEndLabels)
			pEndLabels->Push (pResult);

		return pResult;
	}
	else
	{
		err_type = ietSyntax;
		return NULL;
	}
}

LABEL *ITERACTIVEPARSER::evaluate_until (LABEL *pEndJump, STACK *pEndLabels)
{
	// evaluate_until - avalia o até
	LABEL *pResult;

	// verifica se é um erro
	if (tok_type == ittError)
	{
		err_type = ietSyntax;
		return NULL;
	}

	// verifica se o item atual é uma função (teste)
	if (tok_type == ittFunction)
	{
		// aloca espaço para o rótulo criado
		if (!(pResult = pProgram->AddLabel ()))
		{
			err_type = ietMemory;
			return NULL;
		}

		// adiciona na lista e atualiza propriedades
		pResult->lType = ltTest;
		pResult->nIdx = pProgram->Count () - 1;
		pResult->pTrue = pEndJump;

		// salva o nome da função
		pResult->SetData (token);
		// pega o próximo token
		get_token ();

		// verifica se é uma chamada de macro
		if ((tok_type == ittDelimiter) && (token[0] == '('))
		{
			// pega o próximo token
			get_token ();
			// é uma chamada de macro
			pResult->lType = ltMacroTest;
			if (!evaluate_params (pResult->pParams, pResult->nParamsCount))
				return NULL;
		}

		// verifica se é um faça
		if (tok_type != ittDo)
		{
			err_type = ietDoExpected;
			return NULL;
		}
		// neste caso é um faça, então pega o próximo token
		get_token ();

		// avalia a instrução
		if (!evaluate_instruction (pResult->pFalse, pResult, pResult, NULL, true))
			return NULL;

		// adiciona o ate na pilha
		if (pEndLabels)
			pEndLabels->Push (pResult);

		return pResult;
	}
	else
	{
		err_type = ietSyntax;
		return NULL;
	}
}

bool ITERACTIVEPARSER::evaluate_params (char **&pParams, unsigned int &nParamsCount)
{
	// evaluate_params - avalia os parâmetros de uma macro
	pParams = NULL;
	nParamsCount = 0;

	while (tok_type == ittFunction)
	{
		// atualiza o número de parâmetros
		nParamsCount++;
		// tenta alocar memória
		if (!(pParams = (char**) realloc (pParams, nParamsCount * sizeof(char*))))
		{
			nParamsCount = 0;
			err_type = ietMemory;
			return false;
		}
		if (!(pParams[nParamsCount - 1] = (char*) malloc ((strlen (token) + 1) * sizeof(char))))
		{
			nParamsCount--;
			err_type = ietMemory;
			goto error;
		}
		// copia o parâmetro
		strcpy (pParams[nParamsCount - 1], token);
		// pega o próximo token
		get_token ();
		// verifica se é uma vírgula
		if ((tok_type == ittDelimiter) && (token[0] == ','))
		{
			// pega o próximo token
			get_token ();
		}
		else if ((tok_type != ittDelimiter) || (token[0] != ')'))
		{
			err_type = ietParenthesisExpected;
			goto error;
		}
	}
	
	if ((tok_type == ittDelimiter) && (token[0] == ')'))
	{
		// pega o próximo token
		get_token ();
		// retorna os parâmetros
		return true;
	}
	else
		err_type = ietParenthesisExpected;

error:
	// ocorreu um erro de memória
	unsigned int i;
	for (i = 0; i < nParamsCount; i++)
		free (pParams[i]);
	free (pParams);
	pParams = NULL;
	nParamsCount = 0;
	return false;
}