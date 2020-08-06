function teste_01()
%teste_01, negativo de uma imagem

im_in  = double( imread('cameraman.tif') );

%negativo

for r = 0:255
  s( 1 + r ) = 255 - r; 
end;

[ rows, cols ] = size ( im_in );

for i = 1:rows
  for j = 1:cols
    im_out( i, j ) = s( im_in( i , j ) + 1 ) ;
  end;
end;   

%---------------------------------------------------------------------
%show imagem original

subplot( 1, 3, 1 ); imshow( mat2gray( im_in ) );

%---------------------------------------------------------------------
%show plot de trafo

subplot( 1, 3, 2 ); plot( 0:255 , s );
axis( [ 0, 255, 0, 255 ] );
xlabel('r')
ylabel('s(r)')

%---------------------------------------------------------------------
%show imagem processada

subplot( 1, 3, 3 ); imshow( mat2gray( im_out ) );
%---------------------------------------------------------------------






