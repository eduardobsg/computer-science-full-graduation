    /* Vértices são representados por objetos do tipo Vertex.  Os vértices de um digrafo são 0,1,..,V-1. */
    #define Vertex int

    /* Um objeto do tipo Edge representa uma aresta com pontas v e w. */
    #define Edge Arc

    /* A função EDGE recebe dois vértices v e w e devolve uma aresta com pontas v e w. */
    #define EDGE ARC

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

