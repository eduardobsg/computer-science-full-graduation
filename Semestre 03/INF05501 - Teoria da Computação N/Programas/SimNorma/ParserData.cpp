/********************************************************************
	IMPLEMENTAÇÃO DAS FUNÇÕES PARSERDATA
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "ParserData.h"


long fsize (FILE *f)
{
	// fsize - retorna o tamanho do arquivo
	long nResult, nPos = ftell (f);
	fseek (f, 0, SEEK_END);
	nResult = ftell (f);
	fseek (f, nPos, SEEK_SET);
	return nResult;
}

char *ExtractFileName (char *lpFilePath)
{
	// ExtractFileName - retorna o nome de um arquivo a partir de um path
	unsigned int nCount = 0;

	// vai ate o fim do path pegando o tamanho dele
	while (*lpFilePath)
	{
		nCount++;
		lpFilePath++;
	}

	// volta até uma barra ou até o inicio
	while (nCount && (*lpFilePath != '\\'))
	{
		nCount--;
		lpFilePath--;
	}

	// atualiza o valor de retorno
	if (*lpFilePath == '\\')
		lpFilePath++;
	return lpFilePath;
}