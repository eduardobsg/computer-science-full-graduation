function correlate()
% = correlate( baseImage, otherImage )
%

baseImage = imread( 'UTK.jpg' );
maskImage = imread( 'T.jpg' );

% FFT padding
pad = 2;

[ bRows bCols ] = size( baseImage );
bPaddingX = bRows * pad;
bPaddingY = bCols * pad;

[ oRows oCols ] = size( maskImage );
oPaddingX = oRows * pad;
oPaddingY = oCols * pad;

% correlation
fbImage = fft2( im2double( baseImage ), bPaddingX, bPaddingY );
fsbImage = fftshift( fbImage );

fmImage = fft2( im2double( maskImage ), bPaddingX, bPaddingY );
fsmImage = fftshift( fmImage );

fmcImage = conj( fmImage );

fOutImage = fbImage .* fmcImage;

padOutImage = ifft2( fOutImage );
outImage = uint8( padOutImage(1:bRows, 1:bCols) );

figure;
subplot(2,2,1); imshow( log( 1+abs( fsbImage ) ), [] );
subplot(2,2,2); imshow( log( 1+abs( fsmImage ) ), [] );

subplot(2,2,[3 4]); imshow( uint8( outImage ) );
