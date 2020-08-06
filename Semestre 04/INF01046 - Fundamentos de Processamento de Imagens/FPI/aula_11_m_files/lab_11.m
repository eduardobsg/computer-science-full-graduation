function lab_11()

%im_in = double(imread ('cameraman.tif'));
im_in = double(imread ('patterns.jpg'));

%-------------------------------------------------------
%dimensões para padding
[rows cols ] = size( im_in )
M = 2 * rows;
N = 2 * cols;

%-------------------------------------------------------
%filtro
x = 0:M-1;
y = 0:N-1;
[ X Y ] = meshgrid ( x, y );

X0 = ceil ( M / 2) + 1;
Y0 = ceil ( N / 2) + 1;

D = sqrt ( ( X - X0 ).^2 + ( Y - Y0 ).^2 );
D0 = 50;

%notch filter
mask = ones( M, N );
mask( rows + 1, cols + 1 ) = 0;

%Ideal Passa Baixas
%mask = double( D <= D0 );

%Butterworth  Passa Baixas
%n = 1;
%mask = 1 ./ ( 1 + ( D ./ D0 ).^ (2 * n ));

%Gaussian  Passa Baixas
%mask = exp ( - ( D.^2 ) ./ ( 2 * ( D0^2 )));

%Passa Altas
%mask = 1 - mask;
%-------------------------------------------------------
% Transformadas de Fourier
% Filtrado no dominio da frequência

DFT  = fft2( im_in, M, N );
DFTC = fftshift( DFT );
GC = mask .* DFTC;
G = ifftshift( GC );

im_out_s = ( real ( ifft2 ( G ) ) );
im_out = im_out_s( 1:rows, 1:cols );

%display

subplot( 3, 2, 1);imshow( uint8 ( im_in ) );
subplot( 3, 2, 2);imshow( log ( 1 + abs ( DFTC )) , [3, 10] );

subplot( 3, 2, 3);imshow( mask , [] );

subplot( 3, 2, 4); mesh( mask(1:20:M, 1:20:N) );
%axis( [0 50 0 50 0 1] );
%colormap([0 0 0]);
axis off;
grid off;
view( -25, 30)

%subplot( 3, 2, 5);imshow( uint8 (im_out_s) );
subplot( 3, 2, 5);imshow( uint8 (im_out) );

subplot( 3, 2, 6);imshow( log ( 1 + abs ( GC )) , [3, 10] );


