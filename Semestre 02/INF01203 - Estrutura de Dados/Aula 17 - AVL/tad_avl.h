//Tipo Exportado
typedef struct TNodoA pNodoA;

//Funções para Árvores AVL
pNodoA rotacao_dupla_esquerda (pNodoA *pt);
pNodoA* rotacao_dupla_direita (pNodoA* pt);
pNodoA* rotacao_esquerda (pNodoA *pt);
pNodoA* rotacao_direita (pNodoA* pt);
int altura (pNodoA a);
int calcula_fator (pNodoA a);
int teste_AVL (pNodoA a); 

