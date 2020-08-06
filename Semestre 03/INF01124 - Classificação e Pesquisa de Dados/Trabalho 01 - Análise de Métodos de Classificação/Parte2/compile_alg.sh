#!/bin/bash

for prog in insertion_sort shell_sort bubble_sort quick_sort heap_sort merge_sort_re; do
   (gcc -o $prog $prog.c) 
done; 


