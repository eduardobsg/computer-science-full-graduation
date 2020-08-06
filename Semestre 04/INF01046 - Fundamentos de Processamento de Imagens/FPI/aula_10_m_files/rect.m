function rect


im_in = zeros ( 512, 512 );
im_in( 256 - 10:256 + 10, 256 - 20 : 256 + 20  ) = 255;

FFT = fftshift( fft2 ( im_in ) );

subplot( 1, 2, 1 ); imshow( im_in );
subplot( 1, 2, 2 ); imshow ( log ( 1 + abs ( FFT ) ), [3, 10] );

%---------------------------------------------------------------------






