function lab_20_02()
%deteccao de linhas
%---------------------------------------------------------------------

im_in  = double(imread('linha.jpg'));
[M,N] = size(im_in);

%mask = Gaussiana;
%im_in  = filtrar(im_in, mask);

mask = LinhaH
im_H  = filtrar(im_in, mask);

mask = LinhaV
im_V  = filtrar(im_in, mask);

mask = Linha45P
im_45P  = filtrar(im_in, mask);

mask = Linha45M
im_45M  = filtrar(im_in, mask);

%im_out = zeros( M, N );
%A = find( im_01 > 200 ); 
%im_out( A ) = 255;

%---------------------------------------------------------------------
%show imagens

subplot( 2, 3, 1 ); imshow( mat2gray( abs( im_in  ) ) );
subplot( 2, 3, 2 ); imshow( mat2gray( abs( im_H   ) ) );
subplot( 2, 3, 3 ); imshow( mat2gray( abs( im_V   ) ) );
subplot( 2, 3, 4 ); imshow( mat2gray( abs( im_45P ) ) );
subplot( 2, 3, 5 ); imshow( mat2gray( abs( im_45M ) ) );

%---------------------------------------------------------------------

function im_out = filtrar( im, mask )
% filtrado optimizado ( ideia de Fabiano Pinto )
delta = 1;
[ rows, cols ] = size ( im );
im_out = zeros( rows, cols );

for l = -delta:delta
  for m = -delta:delta
    im_out(2:rows-1, 2:cols-1) = im_out(2:rows-1, 2:cols-1) + im( 2 + l: rows - 1 + l, 2 + m: cols - 1 + m ) .* mask( l + delta + 1, m + delta + 1 );
  end
end   

 
%---------------------------------------------------------------------
% Gaussiana
function mask = Gaussiana
mask = [ .0625 .125 .0625; 
         .125  .25  .125; 
         .0625 .125 .0625 ]

%---------------------------------------------------------------------
% linhas

function mask = LinhaH1
mask = [  0 -1  0; 
          0  2  0; 
          0 -1  0]
  
function mask = LinhaV1
mask = [  0  0  0; 
         -1  2 -1; 
          0  0  0 ]
  
function mask = Linha45P1
mask = [ -1  0  0; 
          0  2  0; 
          0  0 -1 ]
  
function mask = Linha45M1
mask = [ 0  0 -1; 
         0  2  0; 
        -1  0  0 ]
  
%---------------------------------------------------------------------

function mask = LinhaH
mask = [ -1 -1 -1; 
          2  2  2; 
         -1 -1 -1 ]
  
function mask = LinhaV
mask = [ -1  2 -1; 
         -1  2 -1; 
         -1  2 -1 ]
  
function mask = Linha45P
mask = [ -1 -1  2; 
         -1  2 -1; 
          2 -1 -1 ]
  
function mask = Linha45M
mask = [ 2 -1 -1; 
        -1  2 -1; 
        -1 -1  2 ]
  
