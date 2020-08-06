cidade(portoalegre). 
cidade(brasilia).
pais(brasil).
capital(brasil,brasilia).
estado(rgs).
capital(rgs,portoalegre).
capital_pais(X,Y) :- pais(X) , cidade(Y) , capital(X, Y) .
capital_estado(X,Y) :- estado(X), cidade(Y), capital(X, Y) .
capital(X,Y).
