function outputImage = setGrayLevel( inputImage, grayLevel )
%

oldImage = im2double( inputImage );

if ( size(oldImage,3)>1 )
   oldImage = rgb2gray(oldImage);
end

newImage = round( oldImage*grayLevel )/grayLevel;

outputImage = im2uint8( newImage );
