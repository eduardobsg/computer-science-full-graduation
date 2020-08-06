/*

1)Especificar um TAD arvore que contenha as seguintes funções:

·Função para inserção de nodos em uma ABP que armazene inteiros
·Função para imprimir os nodos usando o caminhamento pré-fixado à esquerda
·Função que recebe um ponteiro para um nodo e calcula a sua altura.

*/

//Estrutura de um nodo
struct TNodoA
{
       int info;
       struct TNodoA *esq; //valores menores que o valor da raiz
       struct TNodoA *dir; //valores maiores que o valor da raiz
};
typedef struct TNodoA pNodoA;

pNodoA* InicializaABP (pNodoA *raiz);
pNodoA* InsereNodoABP (pNodoA *raiz, int val);
void ImprimeABP (pNodoA *raiz);
int AlturaNodoABP (pNodoA *raiznodo);
pNodoA* ConsultaABP (pNodoA *raiz, int val);
int ContaNodosABP (pNodoA *raiz, int ch);
pNodoA* AchaPai (pNodoA *raiz, int ch);
pNodoA* ExcluiNodoABP (pNodoA *raiz, int ch);
