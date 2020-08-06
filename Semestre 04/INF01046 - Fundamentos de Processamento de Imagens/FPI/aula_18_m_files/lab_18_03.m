function lab_18_03
%transformacoes geometricas
im_in = imread('cameraman.tif');
[M,N]= size(im_in);


im_out = zeros(M,N);
im_out(:,:) = 127;

%x  y  coordenadas da imagem original
%xp yp coordenadas da imagem transformada

% funcao de transformacao 
% xp = x
% yp = y0 + alfa * (y-y0)

% funcao de transformacao inversa 
% ( para cada ponto xp yp na imagem transformada 
% da as coordenadas x y na imagem original )

% x = xp
% y = y0 + ( 1 / alfa ) * (yp-y0)

alfa = 0.5;
y0 = M/2;

for xp=1:N
   for yp=1:M
               
     x = xp;
%     alfa dependendo de x     
%     alfa = ( 1 - 3.9 * (  x / N - 0.5 )^2 );
      y = round( y0 + (1 / alfa) * (yp - y0));
     
      if ( x > 0 &  x < N+1 & y > 0 & y < M + 1 )
         im_out( yp,xp ) = im_in(y,x); 
      end;
  end;
end;

subplot( 1, 2, 1); imshow(uint8(im_in));
subplot( 1, 2, 2); imshow(uint8(im_out));