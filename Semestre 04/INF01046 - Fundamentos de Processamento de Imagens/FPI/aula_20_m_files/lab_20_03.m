function lab_20_03()
%deteccao de bordas

im_in  = double(imread('casa.jpg'));

%im_in = zeros(200);
%[X,Y] = meshgrid(1:200, 1:200);
%A = find( (( X-100).^2 + (Y-100).^2 ) < 1000 );
%im_in(A) = 255;

im_out = im_in;

mask =  Gaussiana;
im_out = filtrar(im_in, mask);
%im_out = filtrar(im_out, mask);

mask =  SobelH;
im_outH = filtrar(im_out, mask);

mask =  SobelV;
im_outV = filtrar(im_out, mask);

mask =  Sobel45P;
im_out45P = filtrar(im_out, mask);

mask =  Sobel45M;
im_out45M = filtrar(im_out, mask);

%---------------------------------------------------------------------
%show imagens

subplot( 2, 4, 1 ); imshow( uint8( im_out  ) );

subplot( 2, 4, 2 ); imshow( mat2gray( abs( im_outH ) + abs( im_outV ) ) ) ;
title('H + V');
subplot( 2, 4, 3 ); imshow( mat2gray( abs( im_out45P )+ abs( im_out45M ) ) );
title('45P + 45M');
subplot( 2, 4, 4 ); imshow( mat2gray( abs( im_outH ) + abs( im_outV )+ abs( im_out45P )+ abs( im_out45M ) ) );
title('H + V + 45P + 45M');


subplot( 2, 4, 5 ); imshow( mat2gray( abs( im_outH ) ) );
title('H');
subplot( 2, 4, 6 ); imshow( mat2gray( abs( im_outV ) ) );
title('V');
subplot( 2, 4, 7 ); imshow( mat2gray( abs( im_out45P ) ) );
title('45P');
subplot( 2, 4, 8 ); imshow( mat2gray( abs( im_out45M ) ) );
title('45M');

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
% bordas
% Roberts

function mask = Roberts45P
% mask = [ -1 0; 0 -1 ]
% versão 3x3 
mask = [ -1  0  0; 
          0 -1  0; 
          0  0  0 ]

function mask = Roberts45M
%  mask = [ 0 -1 ; -1 0 ]
% versão 3x3 
mask = [  0 -1  0; 
         -1  0  0; 
          0  0  0 ]

  
%---------------------------------------------------------------------
% bordas
% Prewitt
 
function mask = PrewittH
mask = [ -1 -1 -1; 
          0  0  0;
         -1 -1 -1 ]
  
function mask = PrewittV
mask = [ -1  0  1; 
         -1  0  1; 
         -1  0  1 ]
  
function mask = Prewitt45P
mask = [  0  1  1; 
         -1  0  1; 
         -1 -1  0 ]
  
function mask = Prewitt45M
mask = [ -1 -1  0; 
         -1  0  1; 
          0  1  1 ]
  
%---------------------------------------------------------------------
% bordas
% Sobel

function mask = SobelH
mask = [ -1 -2 -1; 
          0  0  0; 
          1  2  1 ]
  
function mask = SobelV
mask = [ -1  0  1; 
         -2  0  2; 
         -1  0  1 ]
  
function mask = Sobel45P
  mask = [ 0  1  2; 
          -1  0  1; 
          -2 -1  0 ]
  
function mask = Sobel45M
  mask = [ -2 -1  0; 
           -1  0  1;
            0  1  2 ]
  
%---------------------------------------------------------------------

  