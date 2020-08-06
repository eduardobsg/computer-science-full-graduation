function filtro_media2( delta )
%filtro passa baixas, media

masksize = 2 * delta + 1;

im_in  = double(imread('patterns.jpg'));

[ rows, cols ] = size ( im_in );

mask = ones ( masksize );
mask = mask ./ (masksize * masksize )

im_out = zeros( rows, cols );

for i = 1 + delta:rows - delta,
   for j = 1 + delta:cols - delta,
      for l = -delta:delta,
         for m = -delta:delta,
            im_out( i, j ) = im_out( i, j ) + im_in( i + l, j + m ) .* mask( l + delta + 1, m + delta + 1 );
         end
      end
   end
end   


%---------------------------------------------------------------------
%show imagens


subplot( 1, 2, 1 ); imshow( im2uint8( mat2gray( im_in  ) ) );
subplot( 1, 2, 2 ); imshow( im2uint8( mat2gray( im_out ) ) );
%---------------------------------------------------------------------






