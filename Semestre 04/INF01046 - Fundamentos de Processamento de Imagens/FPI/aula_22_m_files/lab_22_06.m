function lab_22_06()
%morfologia - Labeling
%consulte a documentacao do matlab para bwlabel
%---------------------------------------------------------------------

im_in  = double(imread('objetos.png'));
[im_out, num ] = bwlabel(im_in, 4 );
sprintf ( 'Numero de objetos %d', num ) 
%---------------------------------------------------------------------
%show imagens

subplot( 1, 2, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 1, 2, 2 ); imshow( mat2gray(im_out));
title('out');
