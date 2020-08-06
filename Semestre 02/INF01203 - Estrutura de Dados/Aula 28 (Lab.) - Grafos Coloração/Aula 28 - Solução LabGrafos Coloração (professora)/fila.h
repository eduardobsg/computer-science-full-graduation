
struct TipoFila{
       int info;
       TipoFila* prox;
       };

TipoFila* cria_fila(void);
TipoFila* insere (TipoFila *l, int dado);
int vazia (TipoFila* l);
int remove(TipoFila **l);
void imprime(TipoFila* l);


