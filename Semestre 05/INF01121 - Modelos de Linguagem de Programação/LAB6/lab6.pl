fatorial(0,1):-!.
fatorial(N,X):-A is N-1,
	      fatorial(A,R),
	      X is N*R.

concatlst([],L2,L2):-!.
concatlst([X|L],L2,[X|D]):-concatlst(L,L2,D).

% [X|L] => [head|tail]
