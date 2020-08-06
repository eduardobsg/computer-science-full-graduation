/* ------------------------------------------------------------------*/
/* Objetivo:  este programa imprime os valores limites dos tipos de dados numéricos do sistema           */
/* ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int main ()
{
     printf (">>>  Valores Limite do Sistema  >>> \n\n");
     // imprime os valores máximos para valores inteiros
     printf ("\n short maximo: %i \n", SHRT_MAX);
     printf ("\n int maximo: %i \n", INT_MAX);
     printf ("\n long maximo: %li \n", LONG_MAX);
     // ---------------------------------------------------------------
     // Imprime a precisao, o range e o valor máximo de um float
     printf ("\n digitos de precisao float: %i \n", FLT_DIG);
     printf ("\n expoente maximo de um float: %i \n", FLT_MAX_10_EXP);
     printf ("\n float maximo: %e \n\n", FLT_MAX);
     //  --------------------------------------------------------------
     //  Imprime a precisao, o range e o valor máximo de um double
     printf ("\n digitos de precisao double: %i \n", DBL_DIG);
     printf ("\n expoente maximo de um double: %i \n", DBL_MAX_10_EXP);
     printf ("\n double maximo: %e \n\n", DBL_MAX);
     //  --------------------------------------------------------------
     //  Imprime a precisao, o range e o valor máximo de um long
     printf ("\n digitos de precisao long double: %i \n", LDBL_DIG);
     printf ("\n expoente maximo de um long double: %i \n", LDBL_MAX_10_EXP);
     printf ("\n long double maximo: %e \n\n", DBL_MAX);
     //  --------------------------------------------------------------
     system ("PAUSE");
     return 0;
     
}
