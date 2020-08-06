function lab_18_04
%transformacoes geometricas

im_in = imread('cameraman.tif');
[M,N]= size(im_in);

%x  y  coordenadas da imagem original
%xp yp coordenadas da imagem transformada

% pontos de referencia na imagem original
x0 = 10 ; y0 = 10;
x1 = 120; y1 = 20;
x2 = 10 ; y2 = 120;
x3 = 120; y3 = 160;

% pontos de referencia na imagem transformada
x0p = 11 ; y0p = 11;
x1p = 121; y1p = 21;
x2p = 11 ; y2p = 121;
x3p = 100; y3p = 120;

% sistema de equacoes a resolver
% A = D . C:  solucao -> C = D \ A
D = [ 
  x0p, y0p, x0p*y0p, 1, 0    , 0  , 0      , 0;
  0  , 0  , 0      , 0, x0p  , y0p, x0p*y0p, 1;
  x1p, y1p, x1p*y1p, 1, 0    , 0  , 0      , 0;
  0  , 0  , 0      , 0, x1p  , y1p, x1p*y1p, 1;
 	x2p, y2p, x2p*y2p, 1, 0    , 0  , 0      , 0;
  0  , 0  , 0      , 0, x2p  , y2p, x2p*y2p, 1;
 	x3p, y3p, x3p*y3p, 1, 0    , 0  , 0      , 0;
  0  , 0  , 0      , 0, x3p  , y3p, x3p*y3p, 1;
];

A = [x0; y0; x1; y1; x2; y2; x3; y3 ];

% solucao do sistema de equacoes linear
% vetor coluna com os coeficientes da transformacao bilinear
C = D \ A;

% aplicamos a transfomacao utilizando vizinhos mais cercanos

im_out = zeros(M,N);
im_out(:,:) = 127;

for xp=1:N
   for yp=1:M
		x = round( C(1) * xp + C(2) * yp + C(3) * xp * yp + C(4) );
    y = round( C(5) * xp + C(6) * yp + C(7) * xp * yp + C(8) );
      
      if ( x > 0 &  x < N+1 & y > 0 & y < M + 1 )
         im_out( yp,xp ) = im_in(y,x); 
      end;
	end;
end;

% desenha os pontos utilizados como referencia
im_in(y0,x0) = 255;
im_in(y1,x1) = 255;
im_in(y2,x2) = 255;
im_in(y3,x3) = 255;

im_out(y0p,x0p) = 255;
im_out(y1p,x1p) = 255;
im_out(y2p,x2p) = 255;
im_out(y3p,x3p) = 255;

%display
subplot( 1, 2, 1); imshow(uint8(im_in));
subplot( 1, 2, 2); imshow(uint8(im_out));