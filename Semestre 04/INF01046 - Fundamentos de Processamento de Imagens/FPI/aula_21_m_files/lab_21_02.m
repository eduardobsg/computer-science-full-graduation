function lab_21_02()
% limiar iterativo 
% a ideia e procurar um limar que cumpra a condição:
% 1- Ser a media aritmetica das medias de tons de cinza do objeto e do fundo
% Para ilustrar o algoritmo o script calcula as medias dos tons de 
% cinza baixo e acima cada ton de cinza e seleciona como limiar 
% aquele que cumpre com a condição 1

%---------------------------------------------------------------------

%im_in  = double(imread('digitais.jpg'));
%im_in  = double(imread('hw3.jpg'));
%im_in  = double(imread('uniform.jpg'));
im_in  = double(imread('nonuniform.jpg'));

[M,N] = size(im_in);

%calculo do histograma
for level = 1:256
   a = find ( im_in == level - 1 ); 
   histograma( level ) = length( a );
end;  

% numero de pixels baixo cada limiar
pixel_count1(1) = histograma( 1 );
for level = 2:256
   pixel_count1(level) = pixel_count1(level-1) + histograma( level );
end;  

% numero de pixels acima de cada limiar
pixel_count2(256) = histograma( 256 );
for level = 255:-1:1
   pixel_count2(level) = pixel_count2(level+1) + histograma( level );
end;  

% media dos tons de cinza baixo cada limiar
acum1 ( 1 ) = 0;
for level = 2:256
  acum1( level ) =  acum1( level - 1 ) +  ( level - 1 ) * histograma( level );
end;  

media1 = zeros ( size(histograma) );
for level = 1:256
  if pixel_count1( level ) > 0 media1( level ) = acum1( level ) / pixel_count1( level ); end; 
end;

% media dos tons de cinza acima de cada limiar
acum2 ( 256 ) = 255 *  histograma( 256 );
for level = 255:-1:1
  acum2( level ) = acum2( level + 1 ) +  ( level - 1 ) * histograma( level );
end;  

media2 = zeros ( size(histograma) );
for level = 1:256
  if pixel_count2( level ) > 0 media2( level ) = acum2( level ) / pixel_count2( level ); end;  
end;

media = ( media1 + media2 ) ./ 2;

% procurar limiar 
T = 0;
for level = 1:256
  if media( level ) > level T = level; end;
end;

%limiarizar
a = find ( im_in > T ); 
im_out = zeros(M,N);
im_out(a) = 255;


%---------------------------------------------------------------------
%show imagens

identidade = 1:256;  

subplot( 2, 2, 1 ); imshow( uint8( im_in ) );
subplot( 2, 2, 2 ); plot( histograma );

subplot( 2, 2, 3 ); 
hold on;
plot( media1, 'g' );
plot( media2, 'r' );
plot( media , 'k' );
plot( identidade , 'b' );
hold off;

subplot( 2, 2, 4 ); 
imshow( uint8( im_out ) );
title (T);