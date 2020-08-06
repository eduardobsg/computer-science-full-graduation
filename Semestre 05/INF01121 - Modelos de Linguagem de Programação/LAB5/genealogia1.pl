% Autor: lwives
% Data: 06/04/2011

pessoa(joao).
pessoa(maria).
pessoa(leonardo).
pessoa(daniele).
pessoa(ana).
pessoa(jose).
pessoa(carla).
pessoa(marcio).
pessoa(fernando).
pessoa(marcelo).
pessoa(vanessa).
pessoa(jaqueline).

% masculino(pessoa).
masculino(joao).
masculino(leonardo).
masculino(jose).
masculino(marcio).
masculino(fernando).
masculino(marcelo).

%feminino(pessoa).
feminino(maria).
feminino(daniele).
feminino(ana).
feminino(carla).
feminino(jaqueline).
feminino(vanessa).

% pai(filho, pai).
pai(ana, joao).
pai(jose, joao).
pai(marcio, joao).
pai(carla, leonardo).
pai(fernando, leonardo).
pai(marcelo, marcio).

% mae(filho, mae).
mae(ana, maria).
mae(jose, maria).
mae(marcio, maria).
mae(carla, daniele).
mae(fernando, daniele).
mae(marcelo, carla).

% gosta(pessoa, pessoa). ou gosta(pessoa, pessoa).
gosta(ana, leitura).
gosta(joao, leitura).
gosta(maria, cinema).
gosta(jose, cinema).
gosta(marcelo, cinema).
gosta(marcelo, vanessa).
gosta(vanessa, marcelo).
gosta(jose, jaqueline).
gosta(leonardo, vinho).
gosta(jose, boliche).

avo(X,Y):-pai(X,Z), pai(Z,Y).
avo(X,Y):-mae(X,Z), pai(Z,Y).
avoh(X,Y):-(pai(X,Z), mae(Z, Y)) ; (mae(X,Z), mae(Z, Y)).
pais(F, P, M):-pai(F, P), mae(F, M).
irmaos(X,Y):-pai(X, P), pai(Y,P), mae(X, M), mae(Y,M), X \= Y.
irmao(X,Y):-irmaos(X,Y), masculino(Y).
irma(X,Y):-irmaos(X,Y), feminino(Y).
tio(X, T):-pais(X, P, M), (irmao(P, T); irmao(M, T)).
tia(X, T):-pais(X, P, M), (irma(P, T); irma(M, T)).
filho(X,Y):-(pai(Y,X);mae(Y,X)),masculino(Y).
filha(X,Y):-(pai(Y,X);mae(Y,X)),feminino(Y).