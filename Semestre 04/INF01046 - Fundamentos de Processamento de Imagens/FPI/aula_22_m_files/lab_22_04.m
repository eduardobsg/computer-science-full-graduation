function lab_22_04()
%morfologia - afinamento
%consulte a documentacao do matlab para bwmorph
%---------------------------------------------------------------------

im_in  = double(imread('digitais.png'));
%im_in  = double(imread('linha.png'));
im_out = double ( bwmorph(im_in, 'thin', inf ) );
%---------------------------------------------------------------------
%show imagens

subplot( 1, 2, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 1, 2, 2 ); imshow( uint8(im_out));
title('out');
