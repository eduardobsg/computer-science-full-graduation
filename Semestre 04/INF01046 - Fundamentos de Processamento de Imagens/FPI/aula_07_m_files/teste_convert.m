function teste_convert()
%teste_convert, conversão de tipos de imagens
% converção de tipos de dados do matlab
% não alteram escalas de tons de cinza:
% uint8, double 
% converção de tipos de imagens do image proc. toolbox
% alteram escalas de tons de cinza:
% im2uint8 imagem uint8 ou double para imagem uint8 [0,255]
% im2double converte im uint8 para imagem double [0,1]
% mat2gray converte matriz tipo double para imagem double [0,1]

im1  = imread('cameraman.tif'); %im1: im uint8 [0, 255] OK
disp( 'im1: uint8');
disp( 'alguns pixels de im1');
disp ( im1( 10, 1:5 ));

im2 = double ( im1 );           %im2: noim double [0, 255] NOK
disp( 'im2: double( im1 )');
disp( 'alguns pixels de im2');
disp ( im2( 10, 1:5 ));

im3 = mat2gray ( im2 );         %im3: im double [0, 1] OK
disp( 'im3: mat2gray( im2 )');
disp( 'alguns pixels de im3');
disp ( im3( 10, 1:5 ));

im4 = im2uint8 ( im2 );         %im4: satura todo x  > 1 -> 255  NOK
disp( 'im4: im2uint8( im2 )');
disp( 'alguns pixels de im4');
disp ( im4( 10, 1:5 ));

im5 = im2uint8 ( im3 );         %im3: im uint8 [0, 255] OK
disp( 'im5: im2uint8( im3 )');
disp( 'alguns pixels de im5');
disp ( im5( 10, 1:5 ));

im6 = uint8 ( im2 );             %im6: im uint8 [0, 255] OK
disp( 'im6: uint8( im2 )');
disp( 'alguns pixels de im6');
disp ( im6( 10, 1:5 ));


%---------------------------------------------------------------------
%show imagens

subplot( 2, 3, 1 ); imshow( im1 );
subplot( 2, 3, 2 ); imshow( im2 );
subplot( 2, 3, 3 ); imshow( im3 );
subplot( 2, 3, 4 ); imshow( im4 );
subplot( 2, 3, 5 ); imshow( im5 );
subplot( 2, 3, 6 ); imshow( im6 );

%---------------------------------------------------------------------






