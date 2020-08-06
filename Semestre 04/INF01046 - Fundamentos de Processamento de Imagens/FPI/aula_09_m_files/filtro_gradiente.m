function filtro_gradiente()
%filtro passa altas, gradiente

im_in  = double(imread('lentecontato.jpg'));

[ rows, cols ] = size ( im_in );

mask_y = [ -1 -2 -1; 0 0 0; 1 2 1 ];
mask_x = [ -1 0 1; -2 0 2; -1 0 1 ];


im_out  = zeros( rows, cols );
im_derx = zeros( rows, cols );
im_dery = zeros( rows, cols );
im_grad = zeros( rows, cols );



for i = 2:rows-1
   for j = 2:cols-1
      for l=-1:1
         for m=-1:1
            im_derx( i, j ) = im_derx( i, j ) + im_in( i + l, j + m ) .* mask_x( l + 2, m + 2 );
            im_dery( i, j ) = im_dery( i, j ) + im_in( i + l, j + m ) .* mask_y( l + 2, m + 2 );
         end
      end
   end
end   

im_derx = abs ( im_derx );
im_dery = abs ( im_dery );

im_grad = im_derx + im_dery;
        
%---------------------------------------------------------------------
%show imagens

subplot( 2, 2, 1 ); imshow( uint8( im_in  ) );
subplot( 2, 2, 2 ); imshow( uint8( im_derx ) );
subplot( 2, 2, 3 ); imshow( uint8( im_dery ) );
subplot( 2, 2, 4 ); imshow( uint8( im_grad ) );

%---------------------------------------------------------------------






