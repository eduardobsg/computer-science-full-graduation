<pre><p>#include &lt;stdio.h&gt;
 
void intercala(int p, int q, int r, int v[]){
     int i, j, k, *w;
     w = malloc( (r - p) * sizeof (int) );
     i = p;
     j = q;
     k = 0;
 
     while (i &lt; q &amp;&amp; j &lt; r){
           if (v[i] &lt;= v[j])
              w[k++] = v[i++];
           else
               w[k++] = v[j++];
     }
 
     while (i &lt; q) w[k++] = v[i++];
     while (j &lt; r) w[k++] = v[j++];
 
     for (i = p; i &lt; r; i++)
         v[i] = w[i - p];
 
     free(w);
}
 

void ordenarMergeSort (int n, int v[])
{
   int p, r;
   int b = 1;
   while (b &lt; n) {
      p = 0;
      while (p + b &lt; n) {
         r = p + 2*b;
         if (r &gt; n) r = n;
         intercala (p, p+b, r, v);
         p = p + 2*b; 
      }
      b = 2*b;
   }
}

 
int main(){
    int numeros[] = {10, 20, 55, 3, 16};


    ordenarMergeSort(5, numeros);
 
    int i;
    for (i = 0; i &lt; 5; i++){
        if (i != 0) printf(&quot;, &quot;);
 
        printf(&quot;%d&quot;, numeros[i]);
    }
 
    getchar();
}
</p></pre>