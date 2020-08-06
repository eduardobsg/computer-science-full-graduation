function lab_12_filtinv()
%Filtros do Dominio da frequencia para o dominio espacial
%-------------------------------------------------------
%dimensões 
M = 512;
N = 512;

%-------------------------------------------------------

%filtro
y = 0:M-1;
x = 0:N-1;
[ X Y ] = meshgrid ( x, y );

X0 = ceil ( N / 2) + 1;
Y0 = ceil ( M / 2) + 1;

D = sqrt ( ( X - X0 ).^2 + ( Y - Y0 ).^2 );
D0 = 20;

%notch filter
%mask = ones( M, N );
%mask( rows + 1, cols + 1 ) = 0;

%Ideal Passa Baixas
%mask = double( D <= D0 );

%Butterworth  Passa Baixas
%n = 2;
%mask = 1 ./ ( 1 + ( D ./ D0 ).^ (2 * n ));

%Gaussian  Passa Baixas
%mask = exp ( - ( D.^2 ) ./ ( 2 * ( D0^2 )));

%Passa Altas
%mask = 1 - mask;

%Laplaciano
mask = ( 2 * 3.1416 )^2 * ( (( X - X0 ) / N ).^2 + ( ( Y - Y0 ) / M ).^2 );

%-------------------------------------------------------
%Filtro no dominio espacial
%DFT Inversa
im_out = real (fftshift( ifft2 ( ifftshift( mask ) )));

%=======================================================
%Dominio da frequencia:
%parte real:
subplot( 2, 2, 1); mesh( real( mask(1:20:M, 1:20:N) ) );
%axis( [0 M 0 N 0 2] );
colormap([0 0 0]);
axis off;
grid off;
title('dominio da frequencia');
view( -25, 30)

%parte imaginaria:
hold on
subplot( 2, 2, 1); mesh( imag( mask(1:20:M, 1:20:N) ) );
hold off
%-------------------------------------------------------
%Dominio espacial, detalhe do centro da imagem
delta = 10;
inc = 1;
%imprimir valores do centro da imagem +- delta
%im_out( Y0-delta:Y0+delta, X0-delta:X0+delta )
%grafico
%subplot( 2, 2, 2); mesh( real(im_out( Y0-delta:inc:Y0+delta, X0-delta:inc:X0+delta ) ));

%-------------------------------------------------------
%Dominio espacial

subplot( 2, 2, 2); mesh( abs( im_out(1:8:M, 1:8:N ) ) );
%colormap([0 0 0]);
%axis off;
grid off;
view( -45, 20 )
%title('dominio espacial');

%parte imaginaria:
%zeroref = zeros ( M, N );
%hold on
%subplot( 2, 2, 2); mesh( zeroref(1:20:M, 1:20:N ) );
%hold off

%-------------------------------------------------------
subplot( 2, 2, 3); imshow ( mat2gray( im_out ) );
title('dominio espacial');

linha = im_out( : , Y0 );
subplot( 2, 2, 4); plot ( 1:N,  linha );
title('dominio espacial')
xlabel('x')
ylabel('level')
