    
    #define Vertex int /* Vértices são representados por objetos do tipo Vertex.  Os vértices de um digrafo são 0,1,..,V-1. */
    #define Edge Arc /* Um objeto do tipo Edge representa uma aresta com pontas v e w. */
    #define EDGE ARC /* A função EDGE recebe dois vértices v e w e devolve uma aresta com pontas v e w. */
    
	/* Essa mesma estrutura será usada para representar grafos, mas nesse caso escreveremos "graph" e "Graph" no lugar de "digraph" e "Digraph" */
    #define graph digraph
    #define Graph Digraph
	
	#define maxCST 2
    
    /* Um objeto do tipo Arc representa um arco com ponta inicial v e ponta final w. */
    typedef struct { 
       Vertex v; 
       Vertex w; 
    } Arc;

    /* A função ARC recebe dois vértices v e w e devolve um arco com ponta inicial v e ponta final w. */
    Arc ARC (Vertex v, Vertex w) {
       Arc e;
       e.v = v;
       e.w = w;
       return e;
    }

    /* A estrutura digraph representa um digrafo. O campo adj é um ponteiro para o vetor de listas de adjacência do digrafo, o campo V contém o número de vértices e o campo A contém o número de arcos do digrafo. */
    struct digraph {
       int V; 
       int A; 
       link *adj; 
    };

    /* Um objeto do tipo Digraph contém o endereço de um digraph. */
    typedef struct digraph *Digraph;

    /* A lista de adjacência de um vértice v é composta por nós do tipo node. Um link é um ponteiro para um node. Cada nó da lista contém um vizinho w de v e o endereço do nó seguinte da lista. */
    typedef struct node *link;
    struct node { 
       Vertex w; 
       link next; 
    };

    /* A função NEW recebe um vértice w e o endereço next de um nó e devolve um novo nó x com x.w = w e x.next = next. */
    link NEW (Vertex w, link next) { 
       link x = malloc(sizeof *x);
       x->w = w; 
       x->next = next;     
       return x;                         
    }

	
    void bruteforceKruskal (int *mat)
    { 
       Vertex id[maxV], v, w;
       for (v = 0; v < G->V; v++) id[v] = v;
       while (1) {
          double mincst = maxCST;
          Vertex v0, w0;
          for (v = 0; v < G->V; v++) 
             for (w = 0; w < G->V; w++) 
                if (G->adj[v][w] < mincst && id[v] != id[w]) 
                   mincst = G->adj[v0=v][w0=w];
          if (mincst == maxCST) return; 
          printf("%d-%d\n", v0, w0);
          for (v = 0; v < G->V; v++) 
             if (id[v] == id[w0])
                id[v] = id[v0];
       }
    }

    	
	
	