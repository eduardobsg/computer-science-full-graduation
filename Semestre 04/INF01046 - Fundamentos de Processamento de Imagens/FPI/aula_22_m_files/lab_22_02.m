function lab_22_02()
%morfologia - hit or miss
%---------------------------------------------------------------------

im_in  = double(imread('hit_or_miss.png'));

im_fundo  = zeros(size(im_in));
A = find ( im_in == 0 );
im_fundo( A ) = 255;

% procurar pixels em forma de '+'
B1 = [ 0 1 0; 1 1 1; 0 1 0]
B2 = [ 1 0 1; 0 0 0; 1 0 1]

%erode imagem  A - B1
im_out1 = 255 * double( erode( im_in, B1 ));

%erode fundo   AC - B2
im_out2 = 255 * double( erode( im_fundo, B2 ));

%intersection ( A - B1 ) int ( AC - B2 )  
im_out = bitand( im_out1, im_out2 );

%---------------------------------------------------------------------
%show imagens

subplot( 2, 3, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 2, 3, 2 ); imshow( uint8(im_fundo ));
title('fundo');
subplot( 2, 3, 4 ); imshow( uint8(im_out1));
title('out1');
subplot( 2, 3, 5 ); imshow( uint8(im_out2));
title('out2');
subplot( 2, 3, 6 ); imshow( uint8(im_out));
title('out');



