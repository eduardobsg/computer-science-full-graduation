# Aviões
var a1 >= 0;
var b1 >= 0;
var c1 >= 0;
var a2 >= 0;
var b2 >= 0;
var c2 >= 0;
var a3 >= 0;
var b3 >= 0;
var c3 >= 0;

maximize lucro: 
	600 * a1 + 440 * b1 + 200 * c1 +
	320 * a2 + 260 * b2 + 160 * c2 +
	720 * a3 + 560 * b3 + 280 * c3;

R1: a1 <= 4;
R2: a2 <= 8;
R3: a3 <= 3;
R4: b1 <= 8;
R5: b2 <= 13;
R6: b3 <= 10;
R7: c1 <= 22;
R8: c2 <= 20;
R9: c3 <= 18;

TRECHO1: a1 + b1 + c1 + a3 + b3 + c3 <= 30;
TRECHO2: a3 + b3 + c3 + a2 + b2 + c2 <= 30;

solve;
display a1, a2, a3, b1, b2, b3, c1, c2, c3;
end;
