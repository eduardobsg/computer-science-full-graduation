function outputImage = increaseResolution( inputImage, power )
%

oldImage = im2double( inputImage );

P = 2^power;
newImage = zeros( size(oldImage,1)*P, size(oldImage,2)*P, size(oldImage,3) );

for i = 1:size(newImage,1),
   for j = 1:size(newImage,2),
      for k = 1:size(newImage,3),
         newImage(i,j,k) = oldImage(ceil(i/P), ceil(j/P), k);
      end
   end
end

outputImage = im2uint8( newImage );
