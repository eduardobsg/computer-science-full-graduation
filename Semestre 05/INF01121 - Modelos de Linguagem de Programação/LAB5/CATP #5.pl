% CATP #5 - Linguagem lógica - PROLOG

% Useful hints:
%  trace: initiates the debug
%  notrace: turn off the trace
%  make: recompile / reload the .pl file

% Crie uma regra para imprimir na tela os elementos que fazem parte de uma lista.
printn([]):-!.
printn([H|T]):-writeln(H),printn(T).

% Crie uma regra para retornar o último elemento de uma lista.
lastone([H|[]]):-writeln(H).
lastone([H|T]):-lastone(T).

% Crie uma regra que inverta os elementos de uma lista.
invertlst([],D):-!.
invertlst([H|T],[D|H]):-invertlst(T,D).

% Crie uma regra que remova um elemento de uma lista.
remove(X,[],[]):-!.
remove(X,[X|T],NT):-remove(X,T,NT).
remove(X,[Y|T],[Y|NT]):-remove(X,T,NT).

% Testa se um elemento é mesmo de uma lista
membro(E,[E|_]).
membro(E,[_|T]):-membro(E,T).

% Concatena duas listas
concatlst([],L2,L2):-!.
concatlst([X|L],L2,[X|D]):-concatlst(L,L2,D).

% Crie uma regra que insira um elemento em uma lista ordenada.
insert(E,[H|T1],[H|T2]):-H=<E,insert(E,T1,T2).
insert(E,T2,[E|T2]).




