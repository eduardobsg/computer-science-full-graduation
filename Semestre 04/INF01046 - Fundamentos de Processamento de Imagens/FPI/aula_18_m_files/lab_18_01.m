function lab_18_01()
%Filtro de Wiener
%im_in = double(imread ('book.jpg'));
im_in = double(imread ('coins.jpg'));

%--------------------------------------------------------------------
% Dominio espacial ( todas com padding ):
% f imagem original ( im_in com padding )
% h mascara de degradação
% n ruido 
[ f, h, n ] = fun_degradacao( im_in );

%--------------------------------------------------------------------
% Dominio da frequencia:

% DFT da imagem original
F = fftshift( fft2( f ) );

% DFT da mascara de de gradaçao
H = fftshift( fft2( h ) );

% DFT do ruido
N = fftshift( fft2( n ) );

% DFT da imagem degradada sem ruido
G0 = H .* F;

% DFT da imagem degradada com ruido
GN = G0 + N;

%--------------------------------------------------------------------
% Dominio espacial
% imagem degradada sem ruido
g0 = real( ifft2( ifftshift( G0 )));

% imagem degradada com ruido
gn = real( ifft2( ifftshift( GN )));

%--------------------------------------------------------------------
% aplicar filtro inverso

F0 = G0 ./ H;
NN = N  ./ H;
FN = GN ./ H;

%--------------------------------------------------------------------
% aplicar filtro de wiener
% para K = 1, 0.1 , 0.01, 0.001

H2 = abs(H).* abs(H);

K1 = .001;
K2 = .01;
K3 = .1;
K4 = 1;

FW1 = ( H2 ./ ( H .* (  H2 +  K1 ) ));
FW2 = ( H2 ./ ( H .* (  H2 +  K2 ) ));
FW3 = ( H2 ./ ( H .* (  H2 +  K3 ) ));
FW4 = ( H2 ./ ( H .* (  H2 +  K4 ) ));

%FW4 = 1 ./ H;
%FW4( find ( abs (FW4) > 10 ) ) = 10; 

FW01 = G0 .* FW1;
NWN1 = N  .* FW1;
FWN1 = GN .* FW1;

FW02 = G0 .* FW2;
NWN2 = N  .* FW2;
FWN2 = GN .* FW2;

FW03 = G0 .* FW3;
NWN3 = N  .* FW3;
FWN3 = GN .* FW3;

FW04 = G0 .* FW4;
NWN4 = N  .* FW4;
FWN4 = GN .* FW4;

%--------------------------------------------------------------------
%display

f0 = real( ifft2( ifftshift( F0 )));
nn = real( ifft2( ifftshift( NN )));
fn = real( ifft2( ifftshift( FN )));

fw01 = real( ifft2( ifftshift( FW01 )));
nwn1 = real( ifft2( ifftshift( NWN1 )));
fwn1 = real( ifft2( ifftshift( FWN1 )));

fw02 = real( ifft2( ifftshift( FW02 )));
nwn2 = real( ifft2( ifftshift( NWN2 )));
fwn2 = real( ifft2( ifftshift( FWN2 )));

fw03 = real( ifft2( ifftshift( FW03 )));
nwn3 = real( ifft2( ifftshift( NWN3 )));
fwn3 = real( ifft2( ifftshift( FWN3 )));

fw04 = real( ifft2( ifftshift( FW04 )));
nwn4 = real( ifft2( ifftshift( NWN4 )));
fwn4 = real( ifft2( ifftshift( FWN4 )));


subplot( 3, 6, 1 ); imshow( uint8 (g0));
subplot( 3, 6, 2 ); imshow( uint8 (f0));
subplot( 3, 6, 3 ); imshow( uint8 (fw01));
subplot( 3, 6, 4 ); imshow( uint8 (fw02));
subplot( 3, 6, 5 ); imshow( uint8 (fw03));
subplot( 3, 6, 6 ); imshow( uint8 (fw04));

subplot( 3, 6, 7 ); imshow( uint8 (127 + n));
subplot( 3, 6, 8 ); imshow( uint8 (nn));
subplot( 3, 6, 9 ); imshow( uint8 (nwn1));
subplot( 3, 6, 10 ); imshow( uint8 (nwn2));
subplot( 3, 6, 11 ); imshow( uint8 (nwn3));
subplot( 3, 6, 12 ); imshow( uint8 (nwn4));

subplot( 3, 6, 13 ); imshow( uint8 (gn));
subplot( 3, 6, 14 ); imshow( uint8 (fn));
subplot( 3, 6, 15 ); imshow( uint8 (fwn1));
subplot( 3, 6, 16 ); imshow( uint8 (fwn2));
subplot( 3, 6, 17 ); imshow( uint8 (fwn3));
subplot( 3, 6, 18 ); imshow( uint8 (fwn4));


%figure , imshow( uint8 ( g ) );
%figure , imshow( uint8 ( fp ) );

%---------------------------------------------------------------------


%---------------------------------------------------------------------
function [ f, h, n ] = fun_degradacao( im_in )

delta = 26;
W = 2 * delta + 1;

[M, N] = size(im_in);

% Mp, NP: size with padding (par)
MP = 2 * ceil(( M + W ) / 2 );
NP = 2 * ceil(( N + W ) / 2 );

% Funcao de degradacao H
% no dominio espacial, preparo a mascara centrada 
% com a dimensão incluindo o padding
% e depois mudo o centro para a origem com ifftshift

h = zeros( MP, NP );

for i = -delta:delta
  for j = -delta:delta
    h( j + MP/2 + 1 , i + NP/2 + 1 ) = 1 / (W^2);
  end
end;

h = ifftshift( h );

% f = im_in padded
f = zeros( MP, NP );
f(1:M, 1:N) = im_in;

sigma = 30;
n = gen_ruido( sigma, MP, NP );

%---------------------------------------------------------------------

%---------------------------------------------------------------------
function ruido = gen_ruido( sigma, MP, NP )
 media = 0; 
 ruido = random( 'Normal', media, sigma, MP, NP ); 
