function lab_24_01()

% segmentação e descrição
% a imagem original em tons de cinza é limiarizada
% como os objetos ficam particionados por pequenos gaps
% é aplicada uma operação de closing
% A função bwlabel, procura regiões conexas e rotula cada uma com um numero ( label )
% O tamanho ( area ) de cada objeto ( região conexa ) é calculada
% é construido um histograma de areas
% são selecionados objetos em função de sua area

%---------------------------------------------------------------------
im_in  = double(imread('nuts_bolts.png'));

[M,N] = size(im_in);

%---------------------------------------------------------------------
%limiarizar
T = 114;
a = find ( im_in > T ); 
im_bw1 = zeros(M,N);
im_bw1(a) = 255;

%---------------------------------------------------------------------
% unir partes utilizando closing -> ( dilate + erode )
% structuring element
B = ones(6)
im_bw2 = double( erode( dilate( im_bw1, B ), B ));

%---------------------------------------------------------------------
% identificar objetos ( label )
% num = numero de objetos achados
% im_objs: cada objeto possue ton de cinza = label ( 1 a num ) 

[im_objs, num ] = bwlabel(im_bw2, 4 );

sprintf ( 'Numero de objetos %d', num ) 

%---------------------------------------------------------------------
% calcular areas dos objetos

areas( 1:num ) = 0;
for label = 1:num  
  a = find( im_objs == label );
  areas(label) = length( a );
end;

area_min = min ( areas );
area_max = max ( areas );

sprintf ( 'Area min %d , max:%d', area_min, area_max ) 

%---------------------------------------------------------------------
%histograma de areas
histam( 1:area_max/10 ) = 0;

for label=1:num 
  area = ceil( areas(label) / 10 );
  histam( area ) = histam( area ) + 1;
end;

%---------------------------------------------------------------------
% selecionar objetos grandes ( area > T )

im_out = zeros(M,N);

T = 180;
for i=1:num 
  a = find( im_objs == i );
  area = length( a );
  if ( area > T ) im_out( a ) = 255; end; 
end;

%---------------------------------------------------------------------
%show imagens

identidade = 1:256;  

subplot( 2, 2, 1 ); imshow( uint8( im_in ) );
subplot( 2, 2, 2 ); plot( histam );

subplot( 2, 2, 3 ); 
imshow( mat2gray( im_objs ) );

subplot( 2, 2, 4 ); 
imshow( uint8( im_out ) );

