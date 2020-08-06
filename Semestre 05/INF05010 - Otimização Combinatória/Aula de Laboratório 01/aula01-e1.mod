# Placas e canos
var m;
var n;
maximize lucro: 25 * m + 30 * n;
s.t. c1: m <= 6000;
s.t. c2: n <= 4000;
s.t. c3: m/200 + n/140 <= 40;
s.t. c4: m >= 0;
s.t. c5: n >= 0;
solve;
display m, n;
end;
