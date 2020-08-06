function lab_12_l()
%Laplaciano no dominio da frequencia

im_in = double(imread ('moon.jpg'));

%-------------------------------------------------------
%dimensões para padding
[rows cols ] = size( im_in )
M = 2 * rows;
N = 2 * cols;

%-------------------------------------------------------
%filtro

y = 0:M-1;
x = 0:N-1;
[ X Y ] = meshgrid ( x, y );

X0 = ceil ( N / 2) + 1;
Y0 = ceil ( M / 2) + 1;

D = sqrt ( ( X - X0 ).^2 + ( Y - Y0 ).^2 );

%Laplaciano
mask = ones ( M, N ) + ( 2 * 3.1416 )^2 * ((( X - X0 ) / N ).^2 + ( ( Y - Y0 ) / M ).^2);

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
subplot( 1, 2, 1);imshow( uint8 ( im_in ) );
subplot( 1, 2, 2);imshow( uint8 ( im_out ) );


