function lab_12_lesp()

%Laplaciano do dominio espacial para o dominio da frequencia

%-------------------------------------------------------
%dimensões 
M = 512;
N = 512;
%coordenadas do centro da imagem
RC = M/2 + 1;
CC = N/2 + 1;
%-------------------------------------------------------
%Laplaciano dominio espacial

%mask = [ -1 -1 -1; -1 8 -1; -1 -1 -1 ];
mask = [ 0 -1 0; -1 4 -1; 0 -1 0 ];

im_out_lap = zeros ( M, N );
im_out_lap( RC-1:RC+1, CC-1:CC+1 ) =  - mask;

lapesp = ifftshift( im_out_lap );
%-------------------------------------------------------
%Laplaciano dominio da frequencia

laplaciano = fftshift( fft2 ( lapesp , M, N ) );

%-------------------------------------------------------
%Laplaciano dominio da frequencia

subplot( 1, 2, 1); mesh( real( laplaciano(1:20:M, 1:20:N) ) );
%axis( [0 M 0 N 0 2] );
colormap([0 0 0]);
axis off;
grid off;
view( -25, 30)

hold on
subplot( 1, 2, 1); mesh( imag( laplaciano(1:20:M, 1:20:N) ) );
hold off

%-------------------------------------------------------
%laplaciano dominio espacial

%imprimir valores do centro da imagem
im_out_lap( RC-5:RC+5, CC-5:CC+5 )

%grafico
subplot( 1, 2, 2); mesh( real(im_out_lap( RC-5:RC+5, CC-5:CC+5 ) ));
colormap([0 0 0]);
axis off;
grid off;
view( -45, 20 )



