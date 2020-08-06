function notchfilter1()

im_in = double (imread ('cameraman.tif'));

[rows, cols ] = size ( im_in )

% remover ponto central ( freq = 0 )
mask = ones ( rows, cols );
mask ( 1, 1 ) = 0;

DFT  = fft2( im_in );
G = mask .* DFT;
im_out = uint8( real ( ifft2 ( G ) ));

media = sum ( im_in(:) ) / ( rows * cols );

subplot( 2, 2, 1);imshow( uint8( im_in ) );
subplot( 2, 2, 2);imshow( log ( 1 + abs ( DFT )) , [3, 10] );
subplot( 2, 2, 3);imshow( uint8(im_in - media ) );
subplot( 2, 2, 4);imshow( im_out );
