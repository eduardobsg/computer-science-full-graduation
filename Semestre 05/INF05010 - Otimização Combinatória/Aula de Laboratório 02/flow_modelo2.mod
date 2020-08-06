set VERTICES;
set ARCS within (VERTICES cross VERTICES);

param capacity{ARCS};
param weight{ARCS};
param demand{VERTICES} default 0;

var x{(i,j) in ARCS} >= 0;
var y{(i,j) in ARCS} binary;


minimize cost: sum{(i,j) in ARCS} x[i,j]*weight[i,j];

s.t. CAP {(i,j) in ARCS}: x[i,j]<=capacity[i,j];

s.t. BALANCE{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[i,j] 
        - sum{j in VERTICES: (j,i) in ARCS} x[j,i]
        = demand[i];
        
s.t. NUMBER_ARCS{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} y[i,j] <=2;

s.t. LIMIT_FLOW{(i,j) in ARCS}: x[i,j] <= y[i,j]*capacity[i,j];

end;
