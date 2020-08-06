function lab_12_h()
%Filtro homomorfico

im_in = double(imread ('hw3.jpg'));

%-------------------------------------------------------
%dimensões para padding
[rows cols ] = size( im_in )
M = rows;
N = cols;

%-------------------------------------------------------
%filtro
y = 0:M-1;
x = 0:N-1;
[ X Y ] = meshgrid ( x, y );

X0 = ceil ( N / 2) + 1;
Y0 = ceil ( M / 2) + 1;

D = sqrt ( ( X - X0 ).^2 + ( Y - Y0 ).^2 );
D0 = 50;

%homomorfico

gammaH = 1;
gammaL = 0;
c = 2;
mask = ones( M, N );
mask = gammaL + ( gammaH - gammaL ) * ( 1 - exp ( - c * ( D.^2 ) ./ ( 2 * ( D0^2 ))));

y1 = 0:rows-1;
x1 = 0:cols-1;
[ X1 Y1 ] = meshgrid ( x1, y1 );


Xc = cols / 3;
Yc = rows / 3;

D1 = ( X1 - Xc ).^2 + ( Y1 - Yc ).^2 ;
H2 = 100; 
iluminancia = H2^2 ./ ( H2^2 + D1 );
im_in = im_in .* iluminancia;

%-------------------------------------------------------
% Transformadas de Fourier
% Filtrado no dominio da frequência

logim_in = log ( 1 + im_in );
DFT  = fft2( logim_in, M, N );
%DFT  = fft2( im_in, M, N );

DFTC = fftshift( DFT );

GC = mask .* DFTC;
G = ifftshift( GC );

im_out_s = ( real ( ifft2 ( G ) ) );
im_out = exp ( im_out_s( 1:rows, 1:cols ) );
%im_out = exp ( im_out_s( 1:rows, 1:cols ) );
%im_out = im_out_s( 1:rows, 1:cols );


%display
subplot( 2, 2, 1);imshow( uint8 ( im_in ) );
subplot( 2, 2, 2);imshow( imadjust( mat2gray ( im_out ), [0.4, 0.45], [0, 1], .5) );

%subplot( 3, 2, 1);imshow( uint8 ( im_in ) );
%subplot( 3, 2, 2);imshow( log ( 1 + abs ( DFTC )) , [3, 10] );

%subplot( 3, 2, 3);imshow( mat2gray(mask) , [] );

subplot( 2, 2, 3); mesh( im_in(1:20:rows, 1:20:cols) );
%axis( [0 50 0 50 0 3] );
% colormap([0 0 0]);
axis off;
grid off;
view( -25, 30);

hold on;

subplot( 2, 2, 3); mesh( im_out(10:20:rows-10, 10:20:cols-10) + 400 );
%axis( [0 50 0 50 0 3] );
% colormap([0 0 0]);
axis off;
grid off;
view( -25, 30);
hold off;

%subplot( 3, 2, 5);imshow( uint8 (im_out_s) );
%subplot( 3, 2, 5);imshow( uint8 (im_out) );

%subplot( 3, 2, 6);imshow( mat2gray(im_out) );
%subplot( 3, 2, 6);imshow( log ( 1 + abs ( GC )) , [3, 10] );


