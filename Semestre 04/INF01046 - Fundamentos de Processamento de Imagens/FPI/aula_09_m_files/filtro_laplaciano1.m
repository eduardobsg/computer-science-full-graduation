function filtro_laplaciano()
%filtro passa altas, laplaciano

im_in  = double(imread('lua.jpg'));

[ rows, cols ] = size ( im_in );

%mask = [ 1 1 1; 1 1 1; 1 1 1 ];
%mask = mask ./ 9;

mask = [ -1 -1 -1; -1 8 -1; -1 -1 -1 ];

im_out  = zeros( rows, cols );
im_lap1 = zeros( rows, cols );
im_lap2 = zeros( rows, cols );


for i = 2:rows-1
   for j = 2:cols-1
      for l=-1:1
         for m=-1:1
            im_lap1( i, j ) = im_lap1( i, j ) + im_in( i + l, j + m ) .* mask( l + 2, m + 2 );
         end
      end
   end
end   

im_lap2 = im_lap1 + 127;
im_out = im_in + im_lap1;
im_out1 = im_in + 2 * im_lap1;
im_out2 = im_in + .5 * im_lap1;
          
%---------------------------------------------------------------------
%show imagens

subplot( 3, 2, 1 ); imshow( uint8( im_in  ) );
subplot( 3, 2, 2 ); imshow( uint8( im_lap1 ) );
subplot( 3, 2, 3 ); imshow( uint8( im_lap2 ) );
subplot( 3, 2, 4 ); imshow( uint8( im_out ) );
subplot( 3, 2, 5 ); imshow( uint8( im_out1 ) );
subplot( 3, 2, 6 ); imshow( uint8( im_out2 ) );

%---------------------------------------------------------------------






