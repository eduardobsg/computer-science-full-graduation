function lab_21_01()
%limiarizacao
%---------------------------------------------------------------------
%pontos

%im_in  = double(imread('digitais.jpg'));
%im_in  = double(imread('hw3.jpg'));
%im_in  = double(imread('uniform.jpg'));
%im_in  = double(imread('nonuniform.jpg'));


[M,N] = size(im_in);

for level = 0:255
   a = find ( im_in == level ); 
   histograma_in( level + 1 ) = length( a );
end;  

a = find ( im_in > 55 ); 
im_out1 = zeros(M,N);
im_out1(a) = 255;

a = find ( im_in > 125 ); 
im_out2 = zeros(M,N);
im_out2(a) = 255;

a = find ( im_in > 190 ); 
im_out3 = zeros(M,N);
im_out3(a) = 255;

%---------------------------------------------------------------------
%show imagens

subplot( 2, 3, 1 ); imshow( uint8( im_in ) );
subplot( 2, 3, 2 ); plot( histograma_in );

subplot( 2, 3, 4 ); imshow( uint8( im_out1 ) );
title('T=55');

subplot( 2, 3, 5 ); imshow( uint8( im_out2 ) );
title('T=125');

subplot( 2, 3, 6 ); imshow( uint8( im_out3 ) );
title('T=190');


