function pontolinha( row )
%filtro passa altas, gradiente

im_in  = imread('pontolinha.jpg');

[ rows, cols ] = size ( im_in );
        
%---------------------------------------------------------------------
%show imagens

if ( row < 2 ) | ( row > rows - 2 ) 
   row = 246; 
end;   
   
im_in ( row - 2, : ) = 255;  
im_in ( row + 2, : ) = 255;  

linha = im_in( row, : );

%---------------------------------------------------------------------

subplot( 1, 2, 1 ); imshow( im_in);

subplot( 1, 2, 2 ); plot( 1:cols , linha );
axis( [ 1, cols, 0, 255 ] );
xlabel('x')
ylabel('level')

%---------------------------------------------------------------------






