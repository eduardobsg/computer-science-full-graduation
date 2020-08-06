function lab_22_01()
%morfologia: dilatacao - erosao
%consulte a documentacao do matlab para dilate, erode
%---------------------------------------------------------------------

%im_in  = double(imread('texto.png'));
%im_in  = double(imread('linha.png'));
im_in  = double(imread('digitais.png'));
[M,N] = size(im_in);

%structuring element
B = [ 1 1 1; 1 1 1; 1 1 1]
%B = [ 0 0 0; 0 1 1; 0 0 0]
%B = ones(10)

%dilate
im_out = double( dilate( im_in, B ));

%erode
%im_out = double( erode( im_in, B ));

%close
%im_out = double( erode( dilate( im_in, B ), B ));

%open
%im_out = double( dilate( erode( im_in, B ), B ));

im_dif1 = 255 * im_out - im_in;
im_dif2 = im_in  - 255 * im_out;
%---------------------------------------------------------------------
%show imagens

subplot( 2, 2, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 2, 2, 2 ); imshow( uint8(im_out ));
title('out');
subplot( 2, 2, 3 ); imshow( uint8(im_dif1));
title('out - in');
subplot( 2, 2, 4 ); imshow( uint8(im_dif2));
title('in - out');




