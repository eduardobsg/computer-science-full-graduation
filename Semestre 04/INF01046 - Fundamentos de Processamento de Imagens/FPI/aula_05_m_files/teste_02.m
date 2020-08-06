function teste_02()
%Negativo com vector subscripting

im_in  = double( imread('cameraman.tif') );

r = 0:255;
s( 1 + r ) = 255 - r; 
im_out = s ( im_in + 1 );


%---------------------------------------------------------------------
%show imagem original

subplot( 1, 3, 1 ); imshow( mat2gray( im_in ) );

%---------------------------------------------------------------------
%show plot de trafo

subplot( 1, 3, 2 ); plot( r , s );
axis( [ 0, 255, 0, 255 ] );
xlabel('r')
ylabel('s(r)')

%---------------------------------------------------------------------
%show imagem processada

subplot( 1, 3, 3 ); imshow( mat2gray( im_out ) );

%---------------------------------------------------------------------






