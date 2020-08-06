function lab_22_03()
%morfologia - hit or miss
%consulte a documentacao do matlab para makelut e applylut
%---------------------------------------------------------------------

im_in  = double(imread('hit_or_miss.png'));

lut = makelut( 'x(2,2) & (sum(x(:)) == 2)', 3 );
im_out = double ( applylut(im_in, lut ));

%---------------------------------------------------------------------
%show imagens

subplot( 1, 2, 1 ); imshow( uint8(im_in  ));
title('in');
subplot( 1, 2, 2 ); imshow( uint8(im_out ));
title('out');
