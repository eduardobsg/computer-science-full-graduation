#include "abp.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *pfator, fator = 0;
    pfator = &fator;
    
    pNodoA *raiz_a, *raiz_b, *raiz_c, *raiz_d;
        
    //Inicialização das ABPs
    raiz_a = NULL;
    raiz_b = NULL;
    raiz_c = NULL;
    raiz_d = NULL;
    
    //Árvore A
    raiz_a = InsereArvore(raiz_a, 42);
    raiz_a = InsereArvore(raiz_a, 15);    
    raiz_a = InsereArvore(raiz_a, 6);
    raiz_a = InsereArvore(raiz_a, 27);
    raiz_a = InsereArvore(raiz_a, 20);
    raiz_a = InsereArvore(raiz_a, 88);
    raiz_a = InsereArvore(raiz_a, 63);
    raiz_a = InsereArvore(raiz_a, 94);    
    raiz_a = InsereArvore(raiz_a, 57);
    raiz_a = InsereArvore(raiz_a, 71);
    
    //Árvore B
    raiz_b = InsereArvore(raiz_b, 42);
    raiz_b = InsereArvore(raiz_b, 15);
    raiz_b = InsereArvore(raiz_b, 27);
    raiz_b = InsereArvore(raiz_b, 20);

    //Árvore C
    raiz_c = InsereArvore(raiz_c, 42);
    raiz_c = InsereArvore(raiz_c, 15);
    raiz_c = InsereArvore(raiz_c, 27);
    raiz_c = InsereArvore(raiz_c, 20);
    raiz_c = InsereArvore(raiz_c, 88);
    raiz_c = InsereArvore(raiz_c, 63);
    raiz_c = InsereArvore(raiz_c, 57);
    raiz_c = InsereArvore(raiz_c, 71);
    
    //Árvore D
    raiz_d = InsereArvore(raiz_d, 42);
    raiz_d = InsereArvore(raiz_d, 15);
    raiz_d = InsereArvore(raiz_d, 6);
    raiz_d = InsereArvore(raiz_d, 27);
    raiz_d = InsereArvore(raiz_d, 88);
    raiz_d = InsereArvore(raiz_d, 63);
    raiz_d = InsereArvore(raiz_d, 94);
    
    //Calcula fatores
    fator_ABP (raiz_a, pfator);
    printf ("Fator A = %d\n", fator);
    fator = 0;
    
    fator_ABP (raiz_b, pfator);
    printf ("Fator B = %d\n", fator);
    fator = 0;
    
    fator_ABP (raiz_c, pfator);
    printf ("Fator C = %d\n", fator);
    fator = 0;
    
    fator_ABP (raiz_d, pfator);
    printf ("Fator D = %d\n", fator);
    fator = 0;
    
    system ("pause");
    return 0;
}

