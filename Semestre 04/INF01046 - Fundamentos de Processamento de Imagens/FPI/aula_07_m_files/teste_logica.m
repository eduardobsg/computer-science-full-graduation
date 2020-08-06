function teste_logica()
%teste_logica, teste de operações logicas

im_in  = imread('cameraman.tif');

[ rows, cols ] = size ( im_in );

mask0 = uint8(zeros( rows, cols ));
mask1 = uint8(255 *ones ( rows, cols ));


im_out1 = bitcmp ( im_in , 8 );    % negativo

im_out2 = bitand ( im_in, mask0 ); % 0 
im_out3 = bitand ( im_in, mask1 ); % im_in

im_out4 = bitor  ( im_in, mask0 ); % im_in
im_out5 = bitor  ( im_in, mask1 ); % 255

%---------------------------------------------------------------------
%show imagens

subplot( 3, 2, 1 ); imshow( im_in );
subplot( 3, 2, 2 ); imshow( im_out1 );
subplot( 3, 2, 3 ); imshow( im_out2 );
subplot( 3, 2, 4 ); imshow( im_out3 );
subplot( 3, 2, 5 ); imshow( im_out4 );
subplot( 3, 2, 6 ); imshow( im_out5 );

%---------------------------------------------------------------------






