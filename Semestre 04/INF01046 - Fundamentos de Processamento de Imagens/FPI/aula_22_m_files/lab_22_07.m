function lab_22_07()
%morfologia - bordas
%---------------------------------------------------------------------

im_in  = double(imread('perfil.png'));

%structuring element
B = [ 1 1 1; 1 1 1; 1 1 1]
%dilate
im_out = 255 * double( dilate( im_in, B )) - im_in;

%---------------------------------------------------------------------
%show imagens

subplot( 1, 2, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 1, 2, 2 ); imshow( mat2gray(im_out));
title('out');
