#include <stdio.h>
#include <stdlib.h>

typedef struct TPtPilha TipoPilha;
typedef int TipoInfo;

TipoPilha* InicializaPilha (TipoPilha *Topo);
int Vazia (TipoPilha *Topo);
void ImprimirPilha (TipoPilha *Topo);
TipoPilha* PushPilha (TipoPilha *Topo, TipoInfo Dado);
int PopPilha (TipoPilha **Topo, TipoInfo *Dado);
TipoInfo ConsultaPilha (TipoPilha *Topo);
TipoPilha* DestroiPilha (TipoPilha *Topo);
int ComparaPilhas (TipoPilha *Topo1, TipoPilha *Topo2);
