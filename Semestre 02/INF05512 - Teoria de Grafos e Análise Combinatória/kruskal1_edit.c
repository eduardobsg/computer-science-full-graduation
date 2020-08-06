/*                                                                      *\
   Kruskal's Algorithm : Minimum Spanning Tree on undirected Graphs
   (c) 2008 by Jesko Huettenhain, http://www.uni-bonn.de/~rattle/
       Solution for the programming assignment:

  http://www.or.uni-bonn.de/lectures/ws08/docs/programmieruebung.html

  Compile: gcc -pedantic -Wall -O2 -o kruskal kruskal.c

\*                                                                      */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* defines an edge {v,w} with cost c({v,w}} =: c
   also stores an index i, which is the index of the edge
   in the original input graph. This is required because
   after sorting the edges, we would otherwise not know
   which index it had originally. */
typedef struct 
    { int v,w,c,i; } 
edge;

/* defines a member of the anti-arborescence for the
   UNION-FIND data structure which is used to maintain the
   connected components during a kruskal run. Each node 
   has a link to its father, every father node can
   roughly estimate the depth of its attached tree. */
typedef struct _unode {
    struct _unode *father;
    int depth;
} unode;

/* the readGraph routine reads a graph from an input file,
   returns the number of vertices and edges in the variables
   pointed to by node_count and edge_count, and returns 
   an array of edges or NULL if the input is invalid. */
edge *readGraph(FILE *fp, int *node_count, int *edge_count) {
    edge *edges;
    int v,w;
    /* read number of nodes and number of edges */
    if (fscanf(fp,"%i%i", node_count, edge_count) != 2) {
        printf("invalid file header.\n");
        return NULL;
    }
    /* allocate memory for the edges */
    else if ( (edges=malloc(*edge_count*sizeof(edge))) != NULL ) {
        int i;
        for (i=0;i<*edge_count;i++) {
            if (fscanf(fp,"%i%i%i",&v,&w,&edges[i].c) != 3) {
                printf("invalid edge at %i\n",i);
                free(edges);
                return NULL;
            }
            /* for the sorting that is performed later, we make sure
               that {v,w} = {w,v} is stored such that both are the same
               tuple (v',w') - this is achieved simply by putting the
               smaller index into v'. */
            if (v > w) {
                edges[i].v = w;
                edges[i].w = v;
            } else { 
                edges[i].v = v;
                edges[i].w = w;
            }
            /* remember the index of this edge in the input graph */
            edges[i].i = i;
        }
    }
    else {
        printf("memory fail (%i edges).\n", *edge_count);
    }
    return edges;
}

/* the edgeSort and costSort functions are parameters to a call to
   qsort - edgeSort sorts the edges lexicographically in order to 
   remove parallel edges thereafter while costSort simply sorts by
   edge cost. */
int edgeSort(const edge* e, const edge *f) {   
         if (e->v < f->v) return -1;
    else if (e->v > f->v) return +1;
    else if (e->w < f->w) return -1;
    else                  return (e->w > f->w);
}
int costSort(const edge* e, const edge *f) {
    return (e->c<f->c)?-1:(e->c>f->c);
}

/* this is the FIND routine for the UNION-FIND data structure used
   to maintain the connected components during a kruskal run. We
   run recursively through the anti-arborescence until we find a 
   node with no father (a root). Backtracking, we fix the pointer
   to "father" of every node by which we passed, reaching a better
   amortized running time. */
unode *l_find(unode *a) {
    if (a->father==NULL) return a;
    else return (a->father = l_find(a->father));
}

/* this is the UNION routine of the UNION-FIND structure. We 
   connect the tree with smaller depth to the other one and if both
   have the same depth, we increase depth. */
void l_union(unode *p, unode *q) {
    if (p->depth > q->depth) {
        q->father = p;
    } else if (p->depth<q->depth) {
        p->father = q;
    } else {
        p->father = q;
        p->depth += 1;
    }
}


/* debug routine returning the estimated CPU time in seconds, used
   by this process */
double ticks() {
    return ((double)clock())/CLOCKS_PER_SEC;
}

int main(int argc, char **argv) {
    FILE *fp; /* input file pointer */
    int  m,n; /* edge count and vertex count */
    int  i,k; /* indices for loops */
    int  c,j; /* temporary weight and index variables */
    edge  *E; /* list of edges */
    unode *V; /* connectivity anti-arborescence */
    int   *I; /* used to store the indices of the edges of the MST */
    
    printf("[%06.2f] reading graph from %s ... ", ticks(), argv[1]);
    /* try to read the graph */
    if ( argc>1 && ((fp=fopen(argv[1],"r"))!=NULL) ) {
        if ( (E = readGraph(fp,&n,&m)) == NULL )
            return 1;
        fclose(fp);
        printf("done.\n"
            "[%06.2f] sorting edges lexicographically ... ", ticks());
        /* sort the edges lexicographically, that means:
           (1,2) < (1,3) < (1,7) < (2,3) < (2,5) < ... */
        qsort(E,m,sizeof(edge),
            (int(*)(const void *,const void *)) edgeSort);
        printf("done.\n"
            "[%06.2f] removing parallel edges ... ", ticks());
        /* to remove parallel edges, run through the edge array ... */ 
        for (i=k=0; i<m; k++) {
            /* ... run through one block of parallel edges ... */
            for (j=i,c=E[i++].c; E[i].v==E[i-1].v 
                              && E[i].w==E[i-1].w && i<m; i++)
                /* ... remembering where we attain the minimum weight, */
                if (E[i].c < c) c = E[j=i].c; 
            /* and only store the cost-minimal edge. We overwrite the
               array in-place to avoid memory problems. After the loop
               finishes, k will store the number of edges to be actually
               processed. */
            E[k] = E[j];
        }
        printf("done (%i removed).\n"
            "[%06.2f] sorting edges by weight ... ", m-k, ticks());
        /* set the new m to k and sort by edge costs. */
        qsort(E,m=k,sizeof(edge), 
            (int(*)(const void *,const void *)) costSort);
        printf("done.\n"
            "[%06.2f] launching kruskal ... ", ticks());
        /* Now we allocate memory for the UNION-FIND datastructure 
           and the output index array: */
        c = sizeof(unode)*n + sizeof(int)*(n-1);
        if ((V = malloc(c)) == NULL) {
            printf("memory fail.\n");
            free(E);
            return 1;
        } else {
            memset(V,0,c);
            I=(int*)(V+n);
        }
        /* this is the kruskal algorithm to construct a MST T.
           c will contain the total cost c(T). */
        for (c=k=i=0;i<m;i++) {
            unode *p = l_find(V+E[i].v),
                  *q = l_find(V+E[i].w);
            if (q != p) {     /* v and w are in different components */
                I[k++] = i;   /* add this edge to the tree */
                c += E[i].c;  /* increase the total cost */
                l_union(p,q); /* connect the components p and q */
            }
        }
        printf("done.\n[%06.2f] Total weight: %d\n", ticks(), c);
        /* this is the output routine if we are not debugging */
        printf("%i\n", c); /* output total weight fist */
        for (i=0; i<(n-1); i++)
            printf("%i\tc(%i,%i) = %i\n",
              E[i].i,E[i].v,E[i].w,E[i].c);
        free(V);
        free(E);
    }
    printf("\n\n");
    system("pause");
    return 0;
}

