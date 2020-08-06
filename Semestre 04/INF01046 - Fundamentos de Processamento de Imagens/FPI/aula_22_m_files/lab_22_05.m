function lab_22_05()
%morfologia - esqueleto e prunning 
%consulte a documentacao do matlab para bwmorph
%---------------------------------------------------------------------

im_in  = double(imread('linha.png'));

im_out1 = double ( bwmorph(im_in, 'skel', inf ) );
im_out2 = double ( bwmorph(im_out1, 'spur', inf ) );
%---------------------------------------------------------------------
%show imagens

subplot( 1, 3, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 1, 3, 2 ); imshow( uint8(im_out1));
title('out1');
subplot( 1, 3, 3 ); imshow( uint8(im_out2));
title('out2');

