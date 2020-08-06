struct s_TipoInfoNo{
       char titulo[50];
       char isbn[20];
       int numpag;
       };
       
typedef struct s_TipoInfoNo TipoInfoNo;

struct s_TipoPtNo{
       TipoInfoNo info;
       s_TipoPtNo* prox;
       };

typedef struct s_TipoPtNo TipoPtNo;

TipoPtNo* cria_lista(void);
TipoPtNo* insere_fim (TipoPtNo* l, TipoInfoNo dados);
void imprime(TipoPtNo* l);
TipoPtNo* destroi(TipoPtNo* ptLista);
