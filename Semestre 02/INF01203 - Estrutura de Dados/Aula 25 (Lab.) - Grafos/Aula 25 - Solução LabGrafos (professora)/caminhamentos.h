#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#define max 8
#define true 1
#define false 0

void visita (int vis[max+1], int v);
void DFS (int grafo[max+1][max+1], int v, int vis[max+1]);
void BFS (int grafo[max+1][max+1], int v, int vis[max+1]);
