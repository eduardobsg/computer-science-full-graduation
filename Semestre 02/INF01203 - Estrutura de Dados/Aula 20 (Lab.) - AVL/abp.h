struct TNodoA
{
        int info;
        struct TNodoA *esq;        
        struct TNodoA *dir;        
};
typedef struct TNodoA pNodoA;

pNodoA* InsereArvore(pNodoA *a, int val);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, char chave);
pNodoA* consultaABP2(pNodoA *a, char chave);
int altura (pNodoA *a, int *fator);
void fator_ABP (pNodoA *a, int *fator);

