function lab_17_01()

im_in = double(imread ('amostra_01.jpg'));

%dimensões
[M, N] = size(im_in);

%generar ruido: consulte 'help random' ou digite 'edit random' para mais detalhes
% de comentar o bloco a utilizar
%--------------------------------------------------------------------
%gaussiano
% adicione seu codigo
%--------------------------------------------------------------------
%Rayleigh

a = 10;
b = 10;
ruido = a + random('Rayleigh', b, M, N ); 
%--------------------------------------------------------------------
%Gamma

%a = 10;
%b = 100;
%ruido = random('Gamma', a, b, M, N ); 
%--------------------------------------------------------------------
%Exponencial

%a = 10;
%ruido = 10 * random('Exponential', a, M, N ); 
%--------------------------------------------------------------------
%uniforme

%a = 10;
%b = 100;
%ruido = a + random('Discrete Uniform', b, M, N ); 
%--------------------------------------------------------------------
%salt and pepper

%prob_salt = .01;
%value_salt = 255;
%prob_pepper = .02;
%value_pepper = -255;

%dice = random('Uniform', 0, 1, M, N ); 
%ruido = zeros(M, N);
%ruido ( find( dice < prob_salt )) = value_salt;
%ruido ( find( dice > 1 - prob_pepper )) = value_pepper;
%--------------------------------------------------------------------

%adicionar ruido e truncar valores entre 0 e 255
im_out = double ( uint8 ( im_in + ruido ) );
%ou
%adicionar ruido e re escalar valores entre 0 e 255
%im_out = 255 * mat2gray ( im_in + ruido );

%adicionar ruido a uma imagem uniforme e truncar valores entre 0 e 255
im_ruido = double ( uint8 ( 127 + ruido ) );
%ou
%adicionar ruido a uma imagem uniforme e re escalar valores entre 0 e 255
%im_ruido = 255 * mat2gray ( 127 + ruido );

%--------------------------------------------------------------------
%histogramas

%histograma da imagem original
for level = 0:255
 	a = find ( uint8( im_in ) == level ); 
  	hist_in( level + 1 ) = length( a );
end

%histograma de imagem uniforme com ruido
for level = 0:255
 	a = find ( uint8( im_ruido ) == level ); 
  	hist_ruido( level + 1 ) = length( a );
end

%histograma da imagem com ruido
for level = 0:255
 	a = find ( uint8( im_out ) == level ); 
  	hist_out( level + 1 ) = length( a );
end

%--------------------------------------------------------------------
%display

subplot( 2, 3, 1 );
imshow( uint8 ( im_in ) );
title ('original');

subplot( 2, 3, 2 );
imshow( uint8 ( im_ruido ) );
title ('127 + ruido');

subplot( 2, 3, 3 );
imshow( uint8 ( im_out ) );
title ('original + ruido');

subplot( 2, 3, 4 ); plot( hist_in );
axis( [ 0, 255, 0, max( hist_in ) ] );
xlabel('level')
ylabel('count')

subplot( 2, 3, 5 ); plot( hist_ruido );
axis( [ 0, 255, 0, max( hist_ruido ) ] );
xlabel('level')
ylabel('count')

subplot( 2, 3, 6 ); plot( hist_out );
axis( [ 0, 255, 0, max( hist_out ) ] );
xlabel('level')
ylabel('count')

%--------------------------------------------------------------------
