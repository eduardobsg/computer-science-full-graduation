function filtro_mediana( delta )
%filtro passa baixas, media

masksize = 2 * delta + 1;

im_in  = double(imread('saltpepper.jpg'));

[ rows, cols ] = size ( im_in );

mask = ones ( masksize );
mask = mask ./ (masksize * masksize )

im_out1 = zeros( rows, cols );

for i = 1 + delta:rows - delta,
   for j = 1 + delta:cols - delta,
      for l = -delta:delta,
         for m = -delta:delta,
            im_out1( i, j ) = im_out1( i, j ) + im_in( i + l, j + m ) .* mask( l + delta + 1, m + delta + 1 );
         end
      end
   end
end   

im_out2 = zeros( rows, cols );
nmedio = round ( ( masksize * masksize ) / 2 );

for i = 1 + delta:rows - delta,
   for j = 1 + delta:cols - delta,
      pixels = im_in( i - delta: i + delta, j - delta : j + delta );
      V = sort ( pixels(:) );
      mediana = V ( nmedio );
      im_out2( i, j ) = mediana;
   end
end   

%---------------------------------------------------------------------
%show imagens


subplot( 1, 3, 1 ); imshow( im2uint8( mat2gray( im_in  ) ) );
subplot( 1, 3, 2 ); imshow( im2uint8( mat2gray( im_out1 ) ) );
subplot( 1, 3, 3 ); imshow( im2uint8( mat2gray( im_out2 ) ) );
%---------------------------------------------------------------------






