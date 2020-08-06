function lab_20_01()
%deteccao de pontos
%---------------------------------------------------------------------
%pontos

im_in  = double(imread('ponto.jpg'));
[M,N] = size(im_in);

mask = Laplaciano1
im_01  = filtrar(im_in, mask);

im_out = zeros( M, N );
A = find( im_01 > 200 ); 
im_out( A ) = 255;
%---------------------------------------------------------------------
%linhas



%---------------------------------------------------------------------
%show imagens

subplot( 1, 3, 1 ); imshow( uint8( im_in ) );
subplot( 1, 3, 2 ); imshow( uint8( im_01 ) );
subplot( 1, 3, 3 ); imshow( uint8( im_out ) );

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
% pontos e bordas
% Laplaciano
function mask = Laplaciano1
mask = [ 0 -1  0; 
        -1  4 -1; 
         0 -1  0 ]

function mask = Laplaciano2
mask = [ -1 -1 -1; 
         -1  8 -1; 
         -1 -1 -1 ]

%---------------------------------------------------------------------
% linhas

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
  
%---------------------------------------------------------------------
