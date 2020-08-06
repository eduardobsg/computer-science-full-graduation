function teste_aritmeticas()
%teste_aritmeticas, operações aritmeticas

im1  = double( imread('blood1.png') );
im2  = double( imread('blood2.png') );

im_dif = im1 - im2;
im_sum = im1 + im2;

%---------------------------------------------------------------------
%show imagens

subplot( 2, 2, 1 ); imshow( mat2gray( im1 ) );
subplot( 2, 2, 2 ); imshow( mat2gray( im2 ) );
subplot( 2, 2, 3 ); imshow( mat2gray( im_dif ) );
subplot( 2, 2, 4 ); imshow( mat2gray( im_sum ) );


%---------------------------------------------------------------------






