#!/bin/bash

for prog in insertion_sort shell_sort bubble_sort quick_sort heap_sort merge_sort_re; do
  (echo ---------------------------------------------------) 1>>resultados2.txt;
  (echo $prog.c, entrada crescente, tempo em micro segundos) 1>>resultados2.txt;
  for tipo in i s; do 	
    for val in 500 5000 10000 30000; do 
      (echo tipo=$tipo, tamanho=$val) 1>>resultados2.txt; 
      (./$prog -$tipo -t $val) 1>>resultados2.txt
    done; 
  done;
done;


