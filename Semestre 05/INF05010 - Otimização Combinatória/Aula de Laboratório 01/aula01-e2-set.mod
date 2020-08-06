# Aviões

/* Conjuntos de classes por trecho */
set TRECHO1;
set TRECHO2;
set TRECHO3;

set CLASSES := TRECHO1 union TRECHO2 union TRECHO3;

/* Parametros */
param cost1 {TRECHO1} >= 0;
param cost2 {TRECHO2} >= 0;
param cost3 {TRECHO3} >= 0;
param costs {CLASSES} >= 0;

param max1 {TRECHO1} >= 0;
param max2 {TRECHO2} >= 0;
param max3 {TRECHO3} >= 0;
param max123 {CLASSES} >= 0;

/* Variables */
var class {i in CLASSES} >= 0, <= max123[i];

/* print */
#printf "CLASSES\tOST\tMAX\tVAR\n";
#printf {classe in CLASSES} "%s\t%s\t%s\t%s\n", classe, costs[classe], max123[classe];

maximize profit : sum{i in CLASSES} costs[i] * class[i];

R1: sum{i in TRECHO1} class[i] + sum{j in TRECHO3} class[j] <= 30;
R2: sum{i in TRECHO3} class[i] + sum{j in TRECHO2} class[j] <= 30;

solve;

printf "SOLUTION: \n";
display class;

data;
/* data section */

set TRECHO1 := A1 B1 C1; 
set TRECHO2 := A2 B2 C2;
set TRECHO3 := A3 B3 C3;

param cost1 :=
A1	600
B1	440
C1	200	;

param cost2 :=
A2	320
B2	260
C2	160	;

param cost3 :=
A3	720
B3	560
C3	280	;

param costs :=
A1	600
B1	440
C1	200
A2	320
B2	260
C2	160
A3	720
B3	560
C3	280	;

param max1 :=
A1	4
B1	8
C1	22	;

param max2 :=
A2	8
B2	13
C2	20	;

param max3 :=
A3	3	
B3	10
C3	18	;

param max123 :=
A1	4
B1	8
C1	22
A2	8
B2	13
C2	20	
A3	3	
B3	10
C3	18	;

end;

