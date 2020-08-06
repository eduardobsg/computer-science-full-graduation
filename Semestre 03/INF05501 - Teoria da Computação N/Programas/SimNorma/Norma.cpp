/********************************************************************
	IMPLEMENTAÇÃO DA CLASSE SIMNORMA
	Criação:	31/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "Norma.h"


/********************************************************************
	CLASSE SIMNORMA */

SIMNORMA::SIMNORMA ()
{
	// SIMNORMA - cria a classe de simulação da máquina norma
	pRegs = NULL;
	nRegsCount = 0;
}

SIMNORMA::~SIMNORMA ()
{
	// ~SIMNORMA - destrói a classe de simulação da máquina norma
	DestroyRegs ();
}

void SIMNORMA::DestroyRegs ()
{
	// DestroyRegs - destrói os registradores atuais
	free (pRegs);
	pRegs = NULL;
	nRegsCount = 0;
}

bool SIMNORMA::GrowRegs (unsigned int nNewRegsCount)
{
	// GrowRegs - aumenta o número de registradores se necessário
	if (nNewRegsCount > nRegsCount)
	{
		if (!(pRegs = (unsigned long*) realloc (pRegs, nNewRegsCount * sizeof(unsigned long))))
			return false;
		memset (pRegs + nRegsCount, 0, (nNewRegsCount - nRegsCount) * sizeof(unsigned long));
		nRegsCount = nNewRegsCount;
	}
	return true;
}

unsigned int SIMNORMA::GetRegNumber (char *sReg)
{
	// GetRegNumber - retorna o índice de um registrador
	if (isalpha (*sReg))
	{
		if (isupper (*sReg))
			return *sReg - 'A';
		else
			return *sReg - 'a';
	}
	else
		return atol (sReg) - 1;
}

bool SIMNORMA::CheckProgram ()
{
	// CheckProgram - verifica se todas as intruções incluídas são válidas
	PROGRAM_BASE *pCurProg = pProgram;
	MACRO *pMacro = NULL;
	LABEL *pCurLabel;
	char *sReg = NULL;
	unsigned int i, j, nCount, nCurItem = 0;

	// destrói os registradores atuais
	DestroyRegs ();

	// repete para cada macro e para o programa principal
	do
	{
		// verifica cada rótulo
		nCount = pCurProg->Count ();
		for (i = 0; i < nCount; i++)
		{
			// pega o rótulo
			pCurLabel = (*pCurProg)[i];
			// verifica o rótulo dependendo do seu tipo
			switch (pCurLabel->lType)
			{
			case ltOperation:
				{
					// verifica se a operação existe
					if (!pCurLabel->sData)
						sReg = NULL;
					else if (strnicmp (pCurLabel->sData, N_ADD, 3) == 0)
						sReg = pCurLabel->sData + 3;
					else if (strnicmp (pCurLabel->sData, N_SUB, 4) == 0)
						sReg = pCurLabel->sData + 4;
					else if (strnicmp (pCurLabel->sData, N_PRINT, 6) == 0)
						sReg = pCurLabel->sData + 6;
					else
					{
						err_type = netInvalidOperation;
						err_data = pCurLabel->sData;
						return false;
					}
					break;
				}
			case ltTest:
				{
					// verifica se o teste exite
					if (strnicmp (pCurLabel->sData, N_ZERO, 5) == 0)
						sReg = pCurLabel->sData + 5;
					else
					{
						err_type = netInvalidTest;
						err_data = pCurLabel->sData;
						return false;
					}
					break;
				}
			default:
				sReg = NULL;
			}
			// verifica se o registrador é válido, verifica se é um parâmetro formal
			if (sReg)
			{
				if (!CheckRegister (sReg, pMacro))
				{
					// neste caso o registrador é inválido
					err_type = etInvalidRegister;
					err_data = sReg;
					return false;
				}
				else
				{
					// neste caso o registrador é válido, verifica se não é um parâmetro formal
					if (!pMacro)
						GrowRegs (GetRegNumber (sReg) + 1);
					else if (!pMacro->IsParam (sReg))
						GrowRegs (GetRegNumber (sReg) + 1);
				}
			}
			// se for uma chamada a macro, verifica cada parâmetro
			if ((pCurLabel->lType == ltMacroOperation) || (pCurLabel->lType == ltMacroTest))
			{
				// verifica cada parâmetro
				for (j = 0; j < pCurLabel->nParamsCount; j++)
				{
					if (!CheckRegister (pCurLabel->pParams[j], pMacro))
					{
						// neste caso o registrador é inválido
						err_type = etInvalidRegister;
						err_data = pCurLabel->pParams[j];
						return false;
					}
					else
					{
						// neste caso o registrador é válido, verifica se não é um parâmetro formal
						if (!pMacro)
							GrowRegs (GetRegNumber (pCurLabel->pParams[j]) + 1);
						else if (!pMacro->IsParam (pCurLabel->pParams[j]))
							GrowRegs (GetRegNumber (pCurLabel->pParams[j]) + 1);
					}
				}
			}
		}

		// verifica se a macro tem um teste definido
		if (pMacro)
		{
			if (sReg = pMacro->GetTest ())
			{
				// verifica se o teste exite
				if (strnicmp (sReg, N_ZERO, 5) == 0)
					sReg = sReg + 5;
				else
				{
					err_type = netInvalidTest;
					err_data = sReg;
					return false;
				}
				// verifica se o registrador é válido
				if (!CheckRegister (sReg, pMacro))
				{
					// neste caso o registrador é inválido
					err_type = etInvalidRegister;
					err_data = sReg;
					return false;
				}
				else if (!pMacro->IsParam (sReg))
					GrowRegs (GetRegNumber (sReg) + 1);
			}
		}

		// pega a próxima macro
		if (nCurItem >= pProgram->MacrosCount ())
			pCurProg = NULL;
		else
		{
			pMacro = pProgram->GetMacro (nCurItem++);
			pCurProg = pMacro;
		}
	} while (pCurProg);
	// neste caso o programa é valido
	return true;
}

bool SIMNORMA::CheckRegister (char *sReg, MACRO *pMacro)
{
	// CheckRegister - retorna se um registrador é válido
	if (pMacro)
	{
		if (pMacro->IsParam (sReg))
			return true;
	}

	// verifica se começa com um número ou uma letra
	if (isalpha (*sReg))
	{
		if (strlen (sReg) == 1)
			return true;
	}
	else if (isdigit (*sReg))
	{
		char *lpReg = sReg;
		do
		{
			lpReg++;
		} while (isdigit (*lpReg));
		if (!*lpReg)
			return true;
	}

	// é um registrador inválido
	return false;
}

void SIMNORMA::ClearRegs ()
{
	// ClearRegs - zera todos os registradores
	if (pRegs)
		memset (pRegs, 0, nRegsCount * sizeof(unsigned long));
}

CUR_STEP SIMNORMA::Step (HWND hwndParent, CUR_STEP pCurStep, bool bPrintTuple)
{
	// Step - executa um passo
	LABEL *pCurLabel;
	if (!pCurStep)
		pCurLabel = (*pProgram)[0];
	else
		pCurLabel = pCurStep;

	// imprime a upla
	if (bPrintTuple)
	{
		unsigned int i;
		CString sTuple = "(";
		CString sNumber;

		// cria a tupla
		for (i = 0; i < nRegsCount - 1; i++)
		{
			sNumber.Format ("%d", pRegs[i]);
			sTuple += sNumber + ", ";
		}
		sNumber.Format ("%d", pRegs[nRegsCount - 1]);
		sTuple += sNumber + ")";

		// manda a mensagem para a saída
		SendMessage (hwndParent, WM_NORMAMSG, WNM_PRINT, (LPARAM) sTuple.GetBuffer (sTuple.GetLength ()));
		sTuple.ReleaseBuffer ();
	}

	// verifica qual é o tipo de rótulo atual
	if (pCurLabel->lType == ltOperation)
	{
		// é uma operação, verifica qual é a operação
		if (pCurLabel->sData)
		{
			if (strnicmp (pCurLabel->sData, N_ADD, 3) == 0)
			{
				// executa a operação
				pRegs[GetRegNumber (pCurLabel->sData + 3)]++;
			}
			else if (_strnicmp (pCurLabel->sData, N_SUB, 4) == 0)
			{
				// executa a operação
				unsigned int nRegNumber = GetRegNumber (pCurLabel->sData + 4);
				if (pRegs[nRegNumber])
                    pRegs[nRegNumber]--;
			}
			else if (_strnicmp (pCurLabel->sData, N_PRINT, 6) == 0)
			{
				// imprime o registrador
				CString sReg = (char*) pCurLabel->sData + 6;
				CString sNumber;

				sNumber.Format ("%d", pRegs[GetRegNumber (pCurLabel->sData + 6)]);
				sReg += " = " + sNumber;
				SendMessage (hwndParent, WM_NORMAMSG, WNM_PRINT, (LPARAM) sReg.GetBuffer (sReg.GetLength ()));
				sReg.ReleaseBuffer ();
			}
		}

		// atualiza o fluxo do programa
		pCurLabel = pCurLabel->pTrue;
	}
	else
	{
		// é um teste, verifica qual é o teste
		if (strnicmp (pCurLabel->sData, N_ZERO, 5) == 0)
		{
			// verifica o teste e atualiza o fluxo
			if (!pRegs[GetRegNumber (pCurLabel->sData + 5)])
				pCurLabel = pCurLabel->pTrue;
			else
				pCurLabel = pCurLabel->pFalse;
		}
	}

	// retorna o próximo passo
	return pCurLabel;
}

unsigned long &SIMNORMA::operator[] (unsigned int nIdx)
{
	// [] - pega o valor do registrador
	if (nIdx >= nRegsCount)
		GrowRegs (nIdx + 1);
	return pRegs[nIdx];
}