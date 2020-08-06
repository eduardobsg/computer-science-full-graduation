Problem:    aula01
Rows:       12
Columns:    9
Non-zeros:  30
Status:     OPTIMAL
Objective:  lucro = 19580 (MAXimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 lucro        B          19580                             
     2 R1           NU             4                           4           400 
     3 R2           NU             8                           8            60 
     4 R3           NU             3                           3           260 
     5 R4           NU             8                           8           240 
     6 R5           B              9                          13 
     7 R6           NU            10                          10           100 
     8 R7           B              5                          22 
     9 R8           B              0                          20 
    10 R9           B              0                          18 
    11 TRECHO1      NU            30                          30           200 
    12 TRECHO2      NU            30                          30           260 

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 a1           B              4             0               
     2 b1           B              8             0               
     3 c1           B              5             0               
     4 a2           B              8             0               
     5 b2           B              9             0               
     6 c2           NL             0             0                        -100 
     7 a3           B              3             0               
     8 b3           B             10             0               
     9 c3           NL             0             0                        -180 

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 0.00e+00 on column 0
        max.rel.err = 0.00e+00 on column 0
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
